#include "led.h"



int main()
{
	printf("Start App \n");

	leds_init();
	leds_run();
	leds_set(0x03);
	leds_set(0x07);


	printf("End App \n");



	return 0;
}
