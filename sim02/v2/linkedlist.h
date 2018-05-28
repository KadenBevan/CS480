#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"


// functions
struct LinkedList *list_create(void);
MetaData *list_create_node(char command, char operation[], int cycleTime);
void insert_node(struct LinkedList *list, MetaData *newNode);
int list_distroy(struct LinkedList *list);

//structures
typedef struct LinkedList
{
	long count;
	MetaData *head;

} LinkedList;

#endif