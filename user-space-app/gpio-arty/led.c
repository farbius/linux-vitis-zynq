#include "led.h"


#define XGPIO_DATA_OFFSET	0x0   /**< Data register for 1st channel */
#define XGPIO_DATA2_OFFSET	0x8   /**< Data register for 2nd channel */


int dh;
static unsigned int* virtual_address;
static unsigned int  phys_address = 0x41200000;

// write / read functions
void mem_set(unsigned int* mem_address, int offset, unsigned int value) {
	mem_address[offset>>2] = value;
}

void mem_get(unsigned int* mem_address, int offset, unsigned int *value) {
    *value = mem_address[offset>>2];
}

void leds_init()
{
	
	dh = open("/dev/mem", O_RDWR | O_SYNC);
	virtual_address = mmap(NULL, 65535, PROT_READ | PROT_WRITE, MAP_SHARED, dh, phys_address);
	printf("Virtual address of axi gpio is 0x%8x and physical address is 0x%8x \n", (unsigned int)virtual_address, phys_address);
	mem_set(virtual_address, XGPIO_DATA_OFFSET, 0x00);
	printf("Module successfully initialized \n");
}

void leds_set(int led)
{
	

	printf("run leds_set func \n");
	printf("value is %d \n", led);
	mem_set(virtual_address, XGPIO_DATA_OFFSET, led);
	usleep(200000);

}

unsigned int leds_get()
{
	
	unsigned int val;
	printf("run leds_get func \n");
	mem_get(virtual_address, XGPIO_DATA2_OFFSET, &val);
	printf("value is %d \n", val);
return val;
}

void leds_run()
{
	printf("run leds_run func \n");

	uint8_t led = 0x01;
	mem_set(virtual_address, XGPIO_DATA_OFFSET, led);

	for(int i = 0; i < 3; i ++)
	{
		usleep(200000);
		led <<= 1;
		mem_set(virtual_address, XGPIO_DATA_OFFSET, led);
	}

	for(int i = 0; i < 3; i ++)
	{
		usleep(200000);
		led >>= 1;
		mem_set(virtual_address, XGPIO_DATA_OFFSET, led);
	}

	for(int i = 0; i < 3; i ++)
	{
		usleep(200000);
		led <<= 1;
		mem_set(virtual_address, XGPIO_DATA_OFFSET, led);
	}

	for(int i = 0; i < 3; i ++)
	{
		usleep(200000);
		led >>= 1;
		mem_set(virtual_address, XGPIO_DATA_OFFSET, led);
	}

}

