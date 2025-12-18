#include "bmp280.h"
#include "i2c.h"
#include <stdlib.h>
#include <util/delay.h>

static bmp280_calib_data calib;
static int32_t t_fine;

static uint16_t read16_LE(uint8_t reg)
{
	uint8_t data[2];
	I2C_start();
	I2C_write((BMP280_ADDR << 1) | 0);
	I2C_write(reg);
	I2C_start();
	I2C_write((BMP280_ADDR << 1) | 1);
	data[0] = I2C_readACK();
	data[1] = I2C_readNACK();
	I2C_stop();
	return ((uint16_t)data[1] << 8) | data[0];
}

static int16_t readS16_LE(uint8_t reg)
{
	return (int16_t)read16_LE(reg);
}

void bmp280_init(void)
{
	// odczyt kalibracji
	calib.dig_T1 = read16_LE(0x88);
	calib.dig_T2 = readS16_LE(0x8A);
	calib.dig_T3 = readS16_LE(0x8C);
	calib.dig_P1 = read16_LE(0x8E);
	calib.dig_P2 = readS16_LE(0x90);
	calib.dig_P3 = readS16_LE(0x92);
	calib.dig_P4 = readS16_LE(0x94);
	calib.dig_P5 = readS16_LE(0x96);
	calib.dig_P6 = readS16_LE(0x98);
	calib.dig_P7 = readS16_LE(0x9A);
	calib.dig_P8 = readS16_LE(0x9C);
	calib.dig_P9 = readS16_LE(0x9E);

	// tryb normalny, oversampling x1
	I2C_start();
	I2C_write((BMP280_ADDR << 1) | 0);
	I2C_write(0xF4);
	I2C_write(0x27);
	I2C_stop();

	// config
	I2C_start();
	I2C_write((BMP280_ADDR << 1) | 0);
	I2C_write(0xF5);
	I2C_write(0x00);
	I2C_stop();

	_delay_ms(50);
}

void bmp280_read_raw(int32_t *raw_temp, int32_t *raw_press)
{
	I2C_start();
	I2C_write((BMP280_ADDR << 1) | 0);
	I2C_write(0xF7);      // rejestr zaczyna siê od PRESS_MSB
	I2C_start();
	I2C_write((BMP280_ADDR << 1) | 1);

	uint8_t p_msb  = I2C_readACK();
	uint8_t p_lsb  = I2C_readACK();
	uint8_t p_xlsb = I2C_readACK();
	uint8_t t_msb  = I2C_readACK();
	uint8_t t_lsb  = I2C_readACK();
	uint8_t t_xlsb = I2C_readNACK();
	I2C_stop();

	if (raw_press != NULL)
	{
		*raw_press = ((int32_t)p_msb << 12) |
		((int32_t)p_lsb << 4) |
		(p_xlsb >> 4);
	}

	if (raw_temp != NULL)
	{
		*raw_temp = ((int32_t)t_msb << 12) |
		((int32_t)t_lsb << 4) |
		(t_xlsb >> 4);
	}
}


float bmp280_read_temperature(void)
{
	int32_t raw_temp;
	bmp280_read_raw(&raw_temp, NULL);

	int32_t var1 = ((((raw_temp >> 3) - ((int32_t)calib.dig_T1 << 1))) * calib.dig_T2) >> 11;
	int32_t var2 = (((((raw_temp >> 4) - calib.dig_T1) * ((raw_temp >> 4) - calib.dig_T1)) >> 12) * calib.dig_T3) >> 14;

	t_fine = var1 + var2;
	return ((t_fine * 5 + 128) >> 8) / 100.0f;
}

float bmp280_read_pressure(void)
{
	int32_t raw_temp, raw_press;
	bmp280_read_raw(&raw_temp, &raw_press);
	bmp280_read_temperature(); // aktualizuje t_fine

	int64_t var1, var2, p;
	var1 = ((int64_t)t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)calib.dig_P6;
	var2 = var2 + ((var1 * (int64_t)calib.dig_P5) << 17);
	var2 = var2 + (((int64_t)calib.dig_P4) << 35);
	var1 = ((var1 * var1 * (int64_t)calib.dig_P3) >> 8) + ((var1 * (int64_t)calib.dig_P2) << 12);
	var1 = (((((int64_t)1) << 47) + var1) * (int64_t)calib.dig_P1) >> 33;

	if (var1 == 0) return 0;

	p = 1048576 - raw_press;
	p = (((p << 31) - var2) * 3125) / var1;
	var1 = (((int64_t)calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
	var2 = (((int64_t)calib.dig_P8) * p) >> 19;

	p = ((p + var1 + var2) >> 8) + (((int64_t)calib.dig_P7) << 4);
	return (float)p / 256.0f;
}
