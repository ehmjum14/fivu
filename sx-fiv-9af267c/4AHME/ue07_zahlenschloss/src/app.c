#include "global.h"

#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "app.h"
#include "sys.h"

// defines
#define SW1_PRESSED ((PINC & (1<<PC7)) == 0)
#define SW2_PRESSED ((PINC & (1<<PC6)) == 0)


// declarations and definations

enum State {
  WAIT, S1OK, S2OK, S3OK, S1ERR, S2ERR, S3ERR,
  OK, ERR, END
};
    
enum ButtonState {
  NOTPRESSED, PRESSED
};

volatile struct App app;
volatile uint8_t eventSW1Pressed = 0;
volatile uint8_t eventSW2Pressed = 0;

// functions




void app_init (void)
{
  memset((void *)&app, 0, sizeof(app));
  DDRC = 0;    // Taster PC7 und PC6 auf Eingang
  DDRA = 0x0f; // LED Ports PA0..PA3 auf Ausgang
}


//--------------------------------------------------------

void app_main (void)
{
//  if (SW1_PRESSED) {
//    PORTA &= ~(1 << PA0); // LED ein
//  } else {
//    PORTA |= (1 << PA0); // LED aus
//  }
}

//--------------------------------------------------------

void app_task_1ms (void) {
  static enum State state = WAIT;
  static uint16_t timer = 0;
  
  if (timer > 0) {
    timer--;
  }
  
  switch (state) {
    
    case WAIT:
      if (eventSW1Pressed) {
        eventSW1Pressed = 0;
        state = S1OK;
      } else if (eventSW2Pressed) {
        eventSW2Pressed = 0;
        state = S1ERR;
      }
      sys_setLed(0, 1); // Bereitschafts-LED leuchtet
      sys_setLed(1, 0); // Eingabe-LED
      sys_setLed(2, 0); // Relais
      sys_setLed(3, 0); // Error-LED
      break;
      
    case S1OK:
      if (eventSW1Pressed) {
        eventSW1Pressed = 0;
        state = S2ERR;
      } else if (eventSW2Pressed) {
        eventSW2Pressed = 0;
        state = S2OK;
      }
      sys_setLed(0, 0); // Bereitschafts-LED leuchtet
      sys_setLed(1, 1); // Eingabe-LED
      sys_setLed(2, 0); // Relais
      sys_setLed(3, 0); // Error-LED
      break;      
      
    case S2OK:
      if (eventSW1Pressed) {
        eventSW1Pressed = 0;
        state = S3OK;
      } else if (eventSW2Pressed) {
        eventSW2Pressed = 0;
        state = S3ERR;
      }
      sys_setLed(0, 0); // Bereitschafts-LED leuchtet
      sys_setLed(1, 1); // Eingabe-LED
      sys_setLed(2, 0); // Relais
      sys_setLed(3, 0); // Error-LED
      break;            

    case S3OK:
      if (eventSW1Pressed) {
        eventSW1Pressed = 0;
        state = OK;
        timer = 2000;
      } else if (eventSW2Pressed) {
        eventSW2Pressed = 0;
        state = ERR;
        timer = 2000;
      }
      sys_setLed(0, 0); // Bereitschafts-LED leuchtet
      sys_setLed(1, 1); // Eingabe-LED
      sys_setLed(2, 0); // Relais
      sys_setLed(3, 0); // Error-LED
      break;            
    
    case S1ERR:
      if (eventSW1Pressed || eventSW2Pressed) {
        eventSW1Pressed = 0;
        eventSW2Pressed = 0;
        state = S2ERR;
      }
      sys_setLed(0, 0); // Bereitschafts-LED leuchtet
      sys_setLed(1, 1); // Eingabe-LED
      sys_setLed(2, 0); // Relais
      sys_setLed(3, 0); // Error-LED
      break;  
   
    case S2ERR:
      if (eventSW1Pressed || eventSW2Pressed) {
        eventSW1Pressed = 0;
        eventSW2Pressed = 0;
        state = S3ERR;
      }
      sys_setLed(0, 0); // Bereitschafts-LED leuchtet
      sys_setLed(1, 1); // Eingabe-LED
      sys_setLed(2, 0); // Relais
      sys_setLed(3, 0); // Error-LED
      break;  

    case S3ERR:
      if (eventSW1Pressed || eventSW2Pressed) {
        eventSW1Pressed = 0;
        eventSW2Pressed = 0;
        state = ERR;
        timer = 2000;
      }
      sys_setLed(0, 0); // Bereitschafts-LED leuchtet
      sys_setLed(1, 1); // Eingabe-LED
      sys_setLed(2, 0); // Relais
      sys_setLed(3, 0); // Error-LED
      break;
      
    case OK:
      if (timer == 0) {
        state = END;
      }
      sys_setLed(0, 0); // Bereitschafts-LED leuchtet
      sys_setLed(1, 0); // Eingabe-LED
      sys_setLed(2, 1); // Relais
      sys_setLed(3, 0); // Error-LED
      break;
      
    case ERR:
      if (timer == 0) {
        state = END;
      }
      sys_setLed(0, 0); // Bereitschafts-LED leuchtet
      sys_setLed(1, 0); // Eingabe-LED
      sys_setLed(2, 0); // Relais
      sys_setLed(3, 1); // Error-LED
      break;
      
    case END: 
      state = WAIT;
      sys_setLed(0, 0); // Bereitschafts-LED leuchtet
      sys_setLed(1, 0); // Eingabe-LED
      sys_setLed(2, 0); // Relais
      sys_setLed(3, 0); // Error-LED
  }
  
}

void app_task_2ms (void) {}
void app_task_4ms (void) {}
void app_task_8ms (void) {
  static enum ButtonState sw1State = NOTPRESSED;
  static enum ButtonState sw2State = NOTPRESSED;
  
  switch (sw1State) {
    case NOTPRESSED:
      if (SW1_PRESSED) { // wenn gedrueckt
        sw1State = PRESSED;
      }
      break;

    case PRESSED:
      if (!SW1_PRESSED) { // wenn nicht gedrueckt
        sw1State = NOTPRESSED;
        eventSW1Pressed = 1;
      }
      break;
  }
  
  switch (sw2State) {
    case NOTPRESSED:
      if (SW2_PRESSED) { // wenn gedrueckt
        sw2State = PRESSED;
      }
      break;

    case PRESSED:
      if (!SW2_PRESSED) { // wenn nicht gedrueckt
        sw2State = NOTPRESSED;
        eventSW2Pressed = 1;
      }
      break;
  }
  
}

void app_task_16ms (void) {}
void app_task_32ms (void) {}
void app_task_64ms (void) {}
void app_task_128ms (void) {}



