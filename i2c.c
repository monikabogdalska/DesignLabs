#include <avr/io.h>
#include "i2c.h"

void I2C_init(void)
{
	TWSR0 = 0x00; // prescaler 1
	TWBR0 = 72;   // 100kHz dla F_CPU=16MHz
	TWCR0 = (1<<TWEN);
}

void I2C_start(void)
{
	TWCR0 = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR0 & (1<<TWINT)));
}

void I2C_stop(void)
{
	TWCR0 = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void I2C_write(uint8_t data)
{
	TWDR0 = data;
	TWCR0 = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR0 & (1<<TWINT)));
}

uint8_t I2C_readACK(void)
{
	TWCR0 = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR0 & (1<<TWINT)));
	return TWDR0;
}

uint8_t I2C_readNACK(void)
{
	TWCR0 = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR0 & (1<<TWINT)));
	return TWDR0;
}
