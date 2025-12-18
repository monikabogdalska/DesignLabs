#include "onewire.h"
#include <util/delay.h>

uint8_t onewire_reset(void)
{
	uint8_t r;

	ONEWIRE_DDR |=  (1 << ONEWIRE_BIT);   // linia jako wyjœcie
	ONEWIRE_PORT &= ~(1 << ONEWIRE_BIT);  // 0
	_delay_us(480);

	ONEWIRE_DDR &= ~(1 << ONEWIRE_BIT);   // wejœcie
	_delay_us(70);

	r = (ONEWIRE_PINR & (1 << ONEWIRE_BIT)); // presence

	_delay_us(410);
	return (r == 0); // 1 = sensor obecny
}

void onewire_writebit(uint8_t bit)
{
	ONEWIRE_DDR |=  (1 << ONEWIRE_BIT);
	ONEWIRE_PORT &= ~(1 << ONEWIRE_BIT);
	_delay_us(2);

	if(bit)
	ONEWIRE_DDR &= ~(1 << ONEWIRE_BIT);

	_delay_us(60);
	ONEWIRE_DDR &= ~(1 << ONEWIRE_BIT);
}

uint8_t onewire_readbit(void)
{
	uint8_t r;

	ONEWIRE_DDR |=  (1 << ONEWIRE_BIT);
	ONEWIRE_PORT &= ~(1 << ONEWIRE_BIT);
	_delay_us(2);

	ONEWIRE_DDR &= ~(1 << ONEWIRE_BIT);
	_delay_us(10);

	r = (ONEWIRE_PINR & (1 << ONEWIRE_BIT)) != 0;

	_delay_us(50);
	return r;
}

void onewire_writebyte(uint8_t byte)
{
	for(uint8_t i=0;i<8;i++)
	onewire_writebit(byte & (1<<i));
}

uint8_t onewire_readbyte(void)
{
	uint8_t b = 0;
	for(uint8_t i=0;i<8;i++)
	if(onewire_readbit())
	b |= (1<<i);
	return b;
}
