CC = gcc
LFLAGS = -Wall -std=c99

sim03: Utility.c Utility.h Timer.c Timer.h Threads.c Threads.h Structures.h Scheduler.h Scheduler.c Process_Parser.c Process_Parser.h Output_Handler.c Output_Handler.h MMU.c MMU.h Driver.c Driver.h CPU.c CPU.h Config_Parser.c Config_Parser.h
		gcc -lpthread -Wall -std=c99 Utility.c Utility.h Timer.c Timer.h Threads.c Threads.h Structures.h Scheduler.h Scheduler.c Process_Parser.c Process_Parser.h Output_Handler.c Output_Handler.h MMU.c MMU.h Driver.c Driver.h CPU.c CPU.h Config_Parser.c Config_Parser.h -o sim03.exe

target: dependencies
		action