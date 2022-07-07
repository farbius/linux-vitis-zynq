
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdint.h>




void leds_init();
void leds_run();
void leds_set(int led);
unsigned int leds_get();



