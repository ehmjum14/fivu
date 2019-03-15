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

enum SwitchState { NOTPRESSED, PRESSED };


// declarations and definations

volatile struct App app;


// functions

void app_init (void)
{
  memset((void *)&app, 0, sizeof(app));
}


//--------------------------------------------------------

void app_main (void)
{
//  if (sys_clearEvent(APP_EVENT_SW1_RELEASED)) {
//    printf("Taster SW1 wurde losgelassen\n");
//  }
//  if (sys_clearEvent(APP_EVENT_SW1_SHORT)) {
//    printf("   -> kurz\n");
//  }
//  if (sys_clearEvent(APP_EVENT_SW1_LONG)) {
//    printf("   -> lang");
//  }
  
//  if (sys_clearEvent(APP_EVENT_SW1_RELEASED)) {
//    printf("Taster SW1 wurde losgelassen\n");
//    if (sys_clearEvent(APP_EVENT_SW1_SHORT)) {
//      printf("   -> kurz\n");
//    }
//    if (sys_clearEvent(APP_EVENT_SW1_LONG)) {
//      printf("   -> lang\n");
//    }
//  }
  
  cli();
  int ev1 = sys_clearEvent(APP_EVENT_SW1_RELEASED);
  int ev2 = sys_clearEvent(APP_EVENT_SW1_SHORT);
  int ev3 = sys_clearEvent(APP_EVENT_SW1_LONG);
  sei();
  
  if (ev1) {
    printf("Taster SW1 wurde losgelassen\n");
  }
  if (ev2) {
    printf("   -> kurz\n");
  }
  if (ev3) {
    printf("   -> lang\n");
  }
  
  

  
}

//--------------------------------------------------------

void app_task_1ms (void) {}
void app_task_2ms (void) {}
void app_task_4ms (void) {}

void app_task_8ms (void) {
  static enum SwitchState sw1 = NOTPRESSED;
  static uint8_t timer = 0;
  
  switch (sw1) {
    case PRESSED:
      if (timer < 0xff) {
        timer++;
      }
      if (!SW1_PRESSED) {
        sw1 = NOTPRESSED;
        sys_setEvent(APP_EVENT_SW1_RELEASED);
        sys_setEvent(
          timer < 50 ? APP_EVENT_SW1_SHORT : APP_EVENT_SW1_LONG
        );
      }
      break;
      
    case NOTPRESSED:
      if (SW1_PRESSED) {
        sw1 = PRESSED;
        timer = 0;
      }
      break;
  }
  
}


void app_task_16ms (void) {}
void app_task_32ms (void) {}
void app_task_64ms (void) {}
void app_task_128ms (void) {}



