//***********************************************************************
// AIIT Template Level 1
// ----------------------------------------------------------------------
// Description: Framework without functions for megaAVR microcontrollers
// ----------------------------------------------------------------------
// Created: Aug 21, 2016 (SX)
//***********************************************************************

#include "global.h"

#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "sys.h"
#include "app.h"

// Defines, nur in main.c sichtbar
// ...

// globale Variable, nur in main.c sichtbar
// ...

// Konstante
//...

int main (void)
{
  // DDRB = 32;
  DDRB = 0x20; // PB5 auf Ausgang schalten
  // DDRB |= (1 << PB5);
  
  PORTB = 0x00; // LED aus
  
  while (1) {
    PORTB = 0x20; // LED eingeschaltet
    _delay_ms(250);
    PORTB = 0x00; // LED ausschalten
    _delay_ms(250);
  }
  
          
  return 0;
}
