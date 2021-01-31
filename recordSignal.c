/*
   recordSignal.c

   gcc -o recordSignal recordSignal.c -lpigpio -lrt -lpthread

   sudo ./recordSignal
*/


#include <stdio.h> /* fopen(),  fwrite() */
#include <pigpio.h> /* gpioSetMode(), gpioWrite(), gpioRead(), time_sleep(), gpioTerminate() */
#include <unistd.h> /* sleep() */

#define RECEIVER_PIN 10
#define TRANSMITER_PIN 14
#define RECORD_X_SECONDS 2


FILE *fp;
unsigned int lastTick;

void gpioPinChangedState(int gpio, int btnState, uint32_t tick) {

	fprintf(fp, "%u %d\n", tick-lastTick, btnState);
	lastTick = tick;
}

int main(int argc, char*argv[]) {

	if (gpioInitialise() < 0)
	{
		fprintf(stderr, "pigpio initialisation failed\n");
		return 1;
	}

	/* 1. Open the file */
	if (!(fp = fopen(argv[1],"w"))) {fprintf(stderr, "could not open file for writing."); return 1; }

	/* 2. Set up the DATA PIN */
	gpioSetMode(RECEIVER_PIN, PI_INPUT);
	gpioSetPullUpDown(RECEIVER_PIN, PI_PUD_OFF);

	lastTick = gpioTick();
	gpioSetAlertFunc(RECEIVER_PIN, gpioPinChangedState);
	sleep(RECORD_X_SECONDS);

	/* release resources */
	gpioTerminate();
	fclose(fp);


	

	return 0;
}


