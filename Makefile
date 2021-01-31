all:
	gcc -o recordSignal recordSignal.c -lpigpio -lrt -lpthread
	gcc -o sendSignal sendSignal.c -lpigpio -lrt -lpthread
