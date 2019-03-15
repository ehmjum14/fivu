#include "global.h"

#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "app.h"
#include "sys.h"

// defines


// declarations and definations
enum State { MUXVCC, MSTARTVCC, MUXTEMP, MSTARTTEMP };
enum State state = MUXVCC;

volatile struct App app;


// functions

void app_init (void)
{
  memset((void *)&app, 0, sizeof(app));
  ADMUX = (1 << REFS0) | (1 << ADLAR) | 0x0e; // Bandgap 1.1V
  // Prescaler 128 -> 16MHz / 128 = 125kHz
  ADCSRA = (1 << ADEN) | 
           (1 << ADPS2) | (1 << ADPS1)| (1 << ADPS0); 
}


//--------------------------------------------------------

void app_main (void) {
    float vcc = (1.1 * 256 * 1.016) / ADCH;
    int vk = (int)vcc;
    int nk = (int)((vcc - (float)vk) * 100.0);
    printf("ADCH = 0x%02x  VCC = %d.%02d   \r", ADCH, vk, nk);
}

//--------------------------------------------------------

void app_task_1ms (void) {
    ADCSRA |= (1 << ADSC);
}

void app_task_2ms (void) {}
void app_task_4ms (void) {}
void app_task_8ms (void) {}
void app_task_16ms (void) {}
void app_task_32ms (void) {}
void app_task_64ms (void) {}
void app_task_128ms (void) {}



