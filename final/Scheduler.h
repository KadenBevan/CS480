#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdlib.h>
#include <stdio.h>
#include "Structures.h"
#include "Utility.h"
#include "CPU.h"
#include "Timer.h"

int schedule_jobs(Config *configuration, Process *jobs_list, OutputNode *output, char *timestr);

#endif