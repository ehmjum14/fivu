#include "global.h"

#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "app.h"
#include "sys.h"

volatile struct App app;


void app_init (void)
{
  memset((void *)&app, 0, sizeof(app));
}


void app_main (void)
{
}


