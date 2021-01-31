/*
   sendSignal.c

   gcc -o sendSignal sendSignal.c -lpigpio -lrt -lpthread

   sudo ./sendSignal
*/


#include <stdio.h> /* fopen(),  fwrite() */
#include <pigpio.h> /* gpioSetMode(), gpioWrite(), gpioRead(), time_sleep(), gpioTerminate() */
#include <unistd.h> /* usleep() */

#define RECEIVER_PIN 10
#define TRANSMITER_PIN 14


FILE *fp;


int main(int argc, char*argv[]) {

	if (gpioInitialise() < 0)
	{
		fprintf(stderr, "pigpio initialisation failed\n");
		return 1;
	}

	/* 1. Open the file */
	if (!(fp = fopen(argv[1],"r"))) {fprintf(stderr, "could not open file for reading."); return 1; }

	/* 2. Set up the DATA PIN */
	gpioSetMode(TRANSMITER_PIN, PI_OUTPUT);
	gpioSetPullUpDown(TRANSMITER_PIN, PI_PUD_OFF);


	while(!feof(fp)) {
		unsigned int delay, newState;
		fscanf(fp, "%u %d\n", &delay, &newState);
		usleep(delay);
		gpioWrite(TRANSMITER_PIN, newState);
	}


	/* release resources */
	gpioTerminate();
	fclose(fp);


	

	return 0;
}


