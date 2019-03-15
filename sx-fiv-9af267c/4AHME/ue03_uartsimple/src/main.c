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

void printString (char s[]) 
{
  int size = strlen(s);
  for (int i = 0; i < size; i++)
  {
    // UDR0 = s[i];
    // _delay_ms(1);
    // von Datenblatt Seite 177
      while ( !( UCSR0A & (1<<UDRE0)) )
        ;
      UDR0 = s[i];
  }
}


int main (void)
{
  DDRB = (1 << PB5); // LED-Pin auf Ausgang
  PORTB = 0;
  
  // Uart Konfiguration 57600/8N1
  UBRR0 = 16;
  UCSR0A = 0x00;
  UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = 0x06;
  sei();
  
  while (1) 
  {
    char s[16];
    // Byte wegsenden
      // UDR0 = 'A'; // ASCII Wert 65
    while ( !(UCSR0A & (1<<RXC0)) )
        ;
    char b = UDR0; // RXC0 wird auf 0 gesetzt
    snprintf(s, sizeof(s), "Hallo b=%u\n", (unsigned)b);
    printString(s);
    // _delay_ms(100);
  }
  
  
  return 0;
}

ISR (USART_RX_vect)
{
  char b = UDR0; // Interrupt Request Bit wird
                 // hier zurueckgesetzt
  // PORTB ^= (1 << PB5);
  if (PORTB & (1 << PB5))
  {
      PORTB = 0;  
  }
  else
  {
      PORTB = (1 << PB5);
  }
}
