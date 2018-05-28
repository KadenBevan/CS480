#ifndef THREADS_H
#define THREADS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "Structures.h"
#include "Timer.h"

void* sleep_runner(void* time);

#endif