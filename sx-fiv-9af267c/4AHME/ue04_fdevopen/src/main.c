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

int uartPut (char c, FILE *f) 
{
  if (f != stdout || f != stderr)
  {
    return 1;
  }
  while ( !( UCSR0A & (1<<UDRE0)) )
        ;
  UDR0 = c;
  return 0;
}

int main (void)
{
  // Uart Konfiguration 57600/8N1
  UBRR0 = 16;
  UCSR0A = 0x00;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = 0x06;

  fdevopen(uartPut, NULL);
  
  printf("Guten Abend\n");
  uint16_t x = 0x123f;
  printf("x=%04x\n", x);
  
  
  return 0;
}
