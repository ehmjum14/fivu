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

void task_2ms ()
{
  
}

void task_4ms ()
{
  
}

void task_8ms ()
{
  
}

void task_16ms ()
{
  
}

void task_32ms ()
{
  
}

void task_64ms ()
{
  
}

void task_128ms ()
{
  
}

void task_256ms ()
{
  PORTB ^= (1<<PB5);
}

ISR (TIMER0_OVF_vect) 
{
  // static unsigned char cnt;
  static uint8_t cnt = 0;
  
  cnt++;
  if      (cnt & 0x01) task_2ms();
  else if (cnt & 0x02) task_4ms();
  else if (cnt & 0x04) task_8ms();
  else if (cnt & 0x08) task_16ms();
  else if (cnt & 0x10) task_32ms();
  else if (cnt & 0x20) task_64ms();
  else if (cnt & 0x40) task_128ms();
  else if (cnt & 0x80) task_256ms();
   
  
}