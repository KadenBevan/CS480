#ifndef CPU_H
#define CPU_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "Structures.h"
#include "Utility.h"
#include "Config_Parser.h"
#include "Scheduler.h"
#include "MMU.h"
#include "Threads.h"

int run_process(Process *process, int IOCT, int PCT, OutputNode *output, char *timestr);
int run_task(MetaData *task, Process *process, int IOCT, int PCT, OutputNode *output, char *timestr);

#endif // !CPU_H
