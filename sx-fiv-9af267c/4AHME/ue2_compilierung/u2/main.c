#include <avr/io.h>

int main ()
{
    DDRB  = 0x20; // 0010 0000
    PORTB = 0x20; // 0010 0000

    return 0;
}
