#include "onewire.h"
#include "ds18b20.h"
#include <util/delay.h>

#define CMD_SKIP_ROM        0xCC
#define CMD_CONVERT_T       0x44
#define CMD_READ_SCRATCHPAD 0xBE

uint8_t ds18b20_read_temp(int16_t *temp)
{
	if(!onewire_reset())
	return 0; // brak sensora

	onewire_writebyte(CMD_SKIP_ROM);
	onewire_writebyte(CMD_CONVERT_T);

	// DS18B20 potrzebuje do 750ms
	_delay_ms(750);

	if(!onewire_reset())
	return 0;

	onewire_writebyte(CMD_SKIP_ROM);
	onewire_writebyte(CMD_READ_SCRATCHPAD);

	uint8_t lsb = onewire_readbyte();
	uint8_t msb = onewire_readbyte();

	*temp = (msb << 8) | lsb;
	return 1;
}