#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#define ONEWIRE_PORT PORTD
#define ONEWIRE_DDR  DDRD
#define ONEWIRE_PINR PIND
#define ONEWIRE_BIT  PD2

uint8_t onewire_reset(void);
void onewire_writebit(uint8_t bit);
uint8_t onewire_readbit(void);
void onewire_writebyte(uint8_t byte);
uint8_t onewire_readbyte(void);

#endif
