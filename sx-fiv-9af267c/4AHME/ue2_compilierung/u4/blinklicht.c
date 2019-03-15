#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

char c;

void blinken ()
{
    PORTB = 0x20; // LED ein
    _delay_ms(500);
    PORTB = 0x00; // LED aus
    _delay_ms(500);
}
