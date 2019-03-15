#include <avr/io.h>
#include "blinklicht.h"

int main ()
{
    DDRB = 0x20;   // PB5 auf Ausgang
    PORTB = 0x00;  // LED aus
    while (1) {
        c = 27;
        blinken();
    }
}
