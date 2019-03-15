#include "global.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "sys.h"
#include "app.h"

volatile struct Sys sys;

// functions
// ...


void sys_init (void)
{
  memset((void *)&sys, 0, sizeof(sys));
 _delay_ms(150);
}


void sys_main (void)
{
}

