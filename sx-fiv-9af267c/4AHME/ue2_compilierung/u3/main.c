#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main ()
{

    DDRB = 0x20; // PB5 auf Ausgang
    while (1)
    {
        PORTB = 0x20; // LED ein
        _delay_ms(100);
        PORTB = 0x00; // LED aus
        _delay_ms(500);
    }
}
