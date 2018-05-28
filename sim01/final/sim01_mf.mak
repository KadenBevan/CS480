CC = gcc
DEBUG = -g
CFLAGS = -Wall -std=c99 -c $(DEBUG)
LFLAGS = -Wall -std=c99 $(DEBUG)

sim01: dataProcessor.o driver.o linkedlist.o utility.o
	$(CC) $(LFLAGS) dataProcessor.o driver.o linkedlist.o utility.o -o sim01

dataProcessor.o: dataProcessor.c dataProcessor.h structures.h LinkedList.h linkedlist.c utility.c utility.h
	$(CC) $(CFLAGS) dataProcessor.c

driver.o: driver.c structures.h linkedlist.h dataProcessor.h
	$(CC) $(CFLAGS) driver.c

utility.o: utility.c utility.h
	$(CC) $(CFLAGS) utility.c
	
clean:
	\rm *.o sim01
	
target: dependencies
	action