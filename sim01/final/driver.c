
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "linkedlist.h"
#include "dataProcessor.h"


int main(int argc, char* argv[])
{
	if(argc != 1)
	{
		printf("Command line argument error!\n");
	}
	
	char* fn_config = argv[1];
	LinkedList *linkedlist = NULL;
	linkedlist = list_create();
	
	ConfigData *configData = (ConfigData*)malloc(sizeof(configData));
	
	int error = parse_data(fn_config, configData, linkedlist);
	if(error == 0)
	{
		print_data(configData, linkedlist);
	}
	else
	{
		printf("Error Parsing Data!\n");
	}
	free(configData);
	free(linkedlist);
		
}