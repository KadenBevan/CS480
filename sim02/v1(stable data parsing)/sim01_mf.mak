CC = gcc
LFLAGS = -Wall -std=c99

sim01: dataProcessor.o DataHandler.o driver.o linkedlist.o utility.o
	$(CC) $(LFLAGS) dataProcessor.o DataHandler.o driver.o linkedlist.o utility.o -o sim01

dataProcessor.o: dataProcessor.c dataProcessor.h structures.h linkedlist.h linkedlist.c utility.c utility.h
	$(CC) $(LFLAGS) dataProcessor.c

DataHandler.o: DataHandler.c DataHandler.h dataProcessor.c dataProcessor.h structures.h linkedlist.h linkedlist.c utility.c utility.h
	$(CC) $(LFLAGS) DataHandler.c	

driver.o: driver.c structures.h linkedlist.h dataProcessor.h
	$(CC) $(LFLAGS) driver.c

utility.o: utility.c utility.h
	$(CC) $(LFLAGS) utility.c
	
clean:
	\rm *.o sim01
	
target: dependencies
	action