CC = gcc
LFLAGS = -Wall -std=c99

sim02: driver.c dataProcessor.c dataProcessor.h linkedlist.c linkedlist.h processhandler.c processhandler.h simtimer.c simtimer.h structures.h utility.c utility.h
		gcc -lpthread -Wall -std=c99 driver.c dataProcessor.c dataProcessor.h linkedlist.c linkedlist.h processhandler.c processhandler.h simtimer.c simtimer.h structures.h utility.c utility.h -o sim02

target: dependencies
		action