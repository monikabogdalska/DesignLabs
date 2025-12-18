#ifndef BMP280_H
#define BMP280_H

#include <stdint.h>

#define BMP280_ADDR 0x76

typedef struct {
	uint16_t dig_T1;
	int16_t  dig_T2;
	int16_t  dig_T3;

	uint16_t dig_P1;
	int16_t  dig_P2;
	int16_t  dig_P3;
	int16_t  dig_P4;
	int16_t  dig_P5;
	int16_t  dig_P6;
	int16_t  dig_P7;
	int16_t  dig_P8;
	int16_t  dig_P9;
} bmp280_calib_data;

void bmp280_init(void);
void bmp280_read_raw(int32_t *raw_temp, int32_t *raw_press);
float bmp280_read_temperature(void);
float bmp280_read_pressure(void);

#endif
