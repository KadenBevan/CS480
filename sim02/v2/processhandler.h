#ifndef PROCESSHANDLER_H
#define PROCESSHANDLER_H

#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "linkedlist.h"
#include "utility.h"
#include <unistd.h>
#include "simtimer.h"

int meta_to_pcb_list(LinkedList* metaDataList, ProcessNode* phead, ConfigData* config);
int print_processes(ProcessNode* phead);
int fill_fcfsn(FCFSQueue* queue, ProcessNode* process_list);
int enqueue(FCFSQueue* queue, FCFSNode* node, int priority);
PCB* dequeue(FCFSQueue* queue);
PCB* next_process(FCFSQueue* queue, char* strategy);
int run(PCB* torun, OutputNode* output_head, char* timestr);

#endif