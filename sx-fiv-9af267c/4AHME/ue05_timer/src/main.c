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
  DDRB   = (1<<PB5);
  TCCR0B = (1<<CS01) | (1<<CS00); // Timer ein, 1:64
  TIMSK0 = (1<<TOIE0);
  sei();
  while (1) {
    
  }
  return 0;
}

ISR (TIMER0_OVF_vect) 
{
  // static unsigned char cnt;
  static uint8_t cnt = 0;
  
  cnt++;
  if (cnt == 200) // 200 * 1.024ms
  {
    cnt = 0;
    PORTB ^= (1<<PB5);
  }
}
