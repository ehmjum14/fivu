#include "global.h"

#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "app.h"
#include "sys.h"

// defines
// ...


// declarations and definations

volatile struct App app;

volatile struct Uhr uhr;
volatile enum App_State state = IDLE;


// functions

void app_init (void)
{
  memset((void *)&app, 0, sizeof(app));
  uhr.ms = 0;
  uhr.sec = 0;
  sys_setEvent(APP_EVENT_START_STATEMACHINE);
}


//--------------------------------------------------------

struct Uhr app_getSystemTime() {
  cli();
  struct Uhr rv = uhr;
  sei();
  return rv;
}

void app_printState (enum App_State state) {
  switch (state) {
    case IDLE:   printf("IDLE  "); break;
    case STATE1: printf("STATE1"); break;
    case STATE2: printf("STATE2"); break;
    case STATE3: printf("STATE3"); break;
    case STATE4: printf("STATE4"); break;
    default:     printf("??????"); break;
  }
}

void app_main (void)
{
  if (sys_clearEvent(APP_EVENT_CHANGE_OF_STATE)) {
    printf("\n Neuer State: ");
    app_printState(state);
    printf("\n\n");
  }
  cli();
  struct Uhr localUhr = uhr;
  enum App_State localState = state;
  uint8_t localPB = PORTB;
  sei();
  printf("Time: %2u.%03u   LED:  %3s   State: ",
         localUhr.sec, localUhr.ms, localPB & (1<<PB5) ? "ON" : "OFF");
  app_printState(localState);
  printf("         \r");
}

//--------------------------------------------------------

void app_task_1ms (void) {
  if (uhr.ms < 999) {
    uhr.ms++;
  } else if (uhr.ms >= 999) {
    if (uhr.sec < 59) {
      uhr.ms = 0;
      uhr.sec++;
      if ( (uhr.sec % 15) == 0) {
        sys_setEvent(APP_EVENT_START_STATEMACHINE);
      }
    }
  }
}

void app_task_2ms (void) {
  static uint8_t cnt = 0;
  
  if (state == IDLE) {
    cnt++;
    if (cnt >=50 ) {
      cnt = 0;
      sys_toggleLed();
    }
  }
}

void app_task_4ms (void) {
static uint16_t timer = 0;
  enum App_State oldState = state;
  
  if (timer > 0) {
    timer--;
  }
  
  switch (state) {
    case IDLE: 
      if (sys_clearEvent(APP_EVENT_START_STATEMACHINE)) {
        state = STATE1;
        timer = 1000 / 4;
      }
      break;
      
    case STATE1:   
      sys_setLed(1);
      if (timer == 0) {
        state = STATE2;
        timer = 2000 / 4;
      }
      break;
      
    case STATE2:   
      sys_setLed(0);
      if (timer == 0) {
        state = STATE3;
        timer = 500 / 4;
      }
      break;

    case STATE3:   
      sys_setLed(1);
      if (timer == 0) {
        state = STATE4;
        timer = 3000 / 4;
      }
      break;
    
    case STATE4:
      sys_setLed(0);
      if (timer == 0) {
        state = IDLE;
      }
      break;
     
    default: // Fehler
      state = IDLE;
      timer = 0;
  }
  
  if (state != oldState) {
    sys_setEvent(APP_EVENT_CHANGE_OF_STATE);
  }
}

void app_task_8ms (void) {}
void app_task_16ms (void) {}
void app_task_32ms (void) {}
void app_task_64ms (void) {}
void app_task_128ms (void) {}



