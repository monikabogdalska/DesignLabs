
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>

#include "usart.h"
#include "i2c.h"
#include "bmp280.h"
#include "ds18b20.h" 
#include "onewire.h"

// ZMIENNA VOLATILE - Konieczna dla zmiennych edytowanych w przerwaniu
volatile uint8_t flaga_pomiaru = 0;
volatile int liczba = 0;

int kod1, kod2;
int16_t temp_raw; 

int alfabet(char znak)
{
    switch (znak)
    {
        case '1': kod1 = 0b11001111; kod2 = 0b11111111; break;
        case '2': kod1 = 0b00100111; kod2 = 0b11111101; break;
        case '3': kod1 = 0b10000111; kod2 = 0b11111101; break;
        case '4': kod1 = 0b11001111; kod2 = 0b11111100; break;
        case '5': kod1 = 0b10010111; kod2 = 0b11111100; break;
        case '6': kod1 = 0b00010111; kod2 = 0b11111100; break;
        case '7': kod1 = 0b11000111; kod2 = 0b11111111; break;
        case '8': kod1 = 0b00000111; kod2 = 0b11111100; break;
        case '9': kod1 = 0b10000111; kod2 = 0b11111100; break;
        case '0': kod1 = 0b00000111; kod2 = 0b11111110; break;
        default:  kod1 = 0xFF;       kod2 = 0b11111111; break;
    }
    return kod1;
}

void seg7_init()
{
    DDRB |= (1 << PB0) | (1 << PB1);
    DDRD |= (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
    DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);
}

void display(char znak, int index)
{
    
    // 2. Ustaw segmenty
    alfabet(znak);
    PORTB = kod2;
    PORTD = kod1;
    
    // 3. W³¹cz konkretny wyœwietlacz
    PORTC = index; 
    
    // 4. Krótkie opóŸnienie dla oka
    _delay_ms(2); // 4ms * 4 cyfry = 16ms (ok. 60Hz odœwie¿ania)
}

void timer_init()
{
    TCCR1B |= (1 << WGM12);   // CTC mode
    TCCR1B |= (1 << CS12) | (1 << CS10);  // Preskaler 1024
    OCR1A = 7812;  // Przerwanie co ok 0.5s
    TIMSK1 |= (1 << OCIE1A);
}

// PRZERWANIE 
ISR(TIMER1_COMPA_vect)
{
    flaga_pomiaru = 1; // dajemy sygna³ do pomiarów
}

void wykonaj_pomiary() {
    float temp = bmp280_read_temperature();
    float press = bmp280_read_pressure();

    uart_puts("Temp: ");
    uart_putfloat(temp);
    uart_puts(" C\r\n");

    uart_puts("Press: ");
    uart_putfloat(press);
    uart_puts(" Pa\r\n\r\n");
    
    // Aktualizacja liczby na wyœwietlacz
    

 
    if(ds18b20_read_temp(&temp_raw))
    {
        float tempC = temp_raw / 16.0;
        uart_putfloat(tempC);
        uart_puts("\r\n");
		liczba = (int)tempC;
	}
	
    else
    {
        uart_puts("Blad DS18B20\r\n");
    }
    
}

int main(void)
{   
    I2C_init();
    bmp280_init();
    
    uart_init(BAUD_CALC(115200));
    stdout = &uart0_io;
    stdin = &uart0_io;
    
    seg7_init();
    timer_init();
    
    sei(); // W³¹czamy przerwania
    
    printf("System start\n");

    while(1)
    {
        // 1. SprawdŸ czy czas na pomiar (co 0.5s)
        if (flaga_pomiaru == 1) {
            wykonaj_pomiary(); // To zajmie chwilê, wyœwietlacz mo¿e mrugn¹æ
            flaga_pomiaru = 0; // Kasujemy flagê
        }

        // 2. Obs³uga wyœwietlacza (musi dzia³aæ non-stop)
        char tysiace = liczba / 1000;
        char setki = (liczba / 100) % 10;
        char dziesiatki = (liczba / 10) % 10;
        char jednosci = liczba % 10;
        
        display(tysiace + '0', 0b11111110);
        display(setki + '0',   0b11111101);
        display(dziesiatki + '0', 0b11111011);
        display(jednosci + '0',   0b11110111);
    }
}