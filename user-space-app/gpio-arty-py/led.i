/* File: led.i */
%module led

%{
#define SWIG_FILE_WITH_INIT
#include "led.h"
%}

void leds_init();
void leds_set(int led);
void leds_run();
unsigned int leds_get();

