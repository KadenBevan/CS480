
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "linkedlist.h"
#include "dataProcessor.h"
#include "utility.h"
#include "DataHandler.h"


int main(int argc, char* argv[])
{
	// check args
	if (argc != 2)
	{
		printf("Command line argument error!\n");
		return -1;
	}
	int error = -1;
	// setup linked list
	LinkedList *linkedlist = NULL;
	linkedlist = list_create();
    
	// setup data parsing params 
	char* fn_config = argv[1];
	ConfigData *configData = (ConfigData*)malloc(sizeof(configData));
	// set error to errors from parsing data
	if(configData != NULL)
	{
		error = parse_data(fn_config, configData, linkedlist);
	}
	else
	{
		printf("Memory allocation error!");
	}
	
	// if no errors print data
	if (error == 0)
	{
		print_data(configData, linkedlist);
	}
	else
	{
		printf("Error Parsing Data!\n");
	}

	//convert_data(linkedlist);
	

	// free list and configData
	list_distroy(linkedlist);
	free(configData);
	return 0;
}