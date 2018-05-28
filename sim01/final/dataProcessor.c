#include "dataProcessor.h"

void print_data(ConfigData* config_data, LinkedList* list)
{
	printf("Config File Dump\n=================\n\n");
	printf("Version\t\t\t: %i\n", config_data->version);
	printf("Program file name\t: %s\n", config_data->metaFilePath);
	printf("CPU schedule code\t: %s\n", config_data->scheduleCode);
	printf("Quantum time\t\t: %i\n", config_data->qTime);
	printf("Memory size\t\t: %i\n", config_data->availableMem);
	printf("Process cycle rate\t: %i\n", config_data->PCT);
	printf("I/O cycle rate\t\t: %i\n", config_data->IOCT);
	printf("Log to code\t\t: %s\n", config_data->logTo);
	printf("Log file name\t\t: %s\n", config_data->logFilePath);
	printf("\nMeta-Data File Dump\n====================\n");
	
	MetaData *head = list->head;
	while(head->next != NULL)
	{
		printf("The data item component letter is\t:%c\n", head->command);
		printf("The data item operation string is\t:%s\n", head->operation);
		printf("The data item cycle time is\t\t:%i\n\n", head->cycleTime);
		head = head->next;
	}
	return;
}

int parse_data(char* fn_config, ConfigData* config_data, LinkedList* list)
{
	extract_config(fn_config, config_data);
	if(check_config(config_data) == 0)
	{
		return extract_meta_data(config_data->metaFilePath, list);
	}
	else
		return ATTRIBUTE_EXTRACTION_ERROR;
}

int extract_config(char* fn_config, ConfigData* config_data)
{
	FILE* fh = fopen(fn_config, "r");
	if(fh == NULL)
	{
		return OPEN_FILE_ERROR;
	}
	char line[MAX_ATTRIBUTE_LENGTH];
	while(fgets(line, MAX_ATTRIBUTE_LENGTH, fh) != NULL)
	{
		//if is valid attribute
		sscanf(line, "Version/Phase: %i", &config_data->version);
		sscanf(line, "File Path: %s", config_data->metaFilePath);
		sscanf(line, "CPU Scheduling Code: %s", config_data->scheduleCode);
		sscanf(line, "Quantum Time (cycles): %i", &config_data->qTime);
		sscanf(line, "Memory Available (KB): %i", &config_data->availableMem);
		sscanf(line, "Processor Cycle Time (msec): %i", &config_data->PCT);
		sscanf(line, "I/O Cycle Time (msec): %i", &config_data->IOCT);
		sscanf(line, "Log To: %s", config_data->logTo);
		sscanf(line, "Log File Path: %s", config_data->logFilePath);
	}
	fclose(fh);
	return 0;
}

int check_config(ConfigData* config_data)
{
	int error = 0;
	if(config_data->version > 10 || config_data->version < 0)
	{
		error++;
	}
	else if(config_data->qTime < 0 || config_data->qTime > 100)
	{
		error++;
	}
	else if(config_data->availableMem < 0 || config_data->availableMem > 1048576)
	{
		error++;
	}
	else if(config_data->PCT < 0 || config_data->PCT > 1000)
	{
		error++;
	}
	else if(config_data->IOCT < 0 || config_data->IOCT > 10000)
	{
		error++;
	}
	else if(config_data->metaFilePath == NULL)
	{
		error++;
	}
	else if(config_data->logFilePath == NULL)
	{
		error++;
	}
	else if(config_data->logTo == NULL)
	{
		error++;
	}
	else if(config_data->scheduleCode == NULL)
	{
		error++;
	}
	return error;
}

int extract_meta_data(char* fp_meta_data, LinkedList* list)
{
	// open file
	FILE* fh = fopen(fp_meta_data, "r");
	if(fh == NULL)
	{
		return OPEN_FILE_ERROR;
	}
	// get string line
	char line[MAX_ATTRIBUTE_LENGTH];
	char* str;
	while(fgets(line, MAX_ATTRIBUTE_LENGTH, fh) != NULL)
	{
		str = strtok (line, ":;.");
		while (str != NULL)
		{
			if(strcmp(str, "Start Program Meta-Data Code") != 0 
			   && strcmp(str, "End Program Meta-Data Code") != 0)
			{
				char command = extract_command(str);
				char* operation = extract_operation(str);
				int cycle_time = extract_cycle_time(str);
				if(command != ' ' && operation != NULL && cycle_time >= 0)
				{
					MetaData *newNode = (MetaData*)malloc(sizeof(MetaData));
					newNode = list_create_node(command, operation, cycle_time);
					insert_node(list, newNode);
				}
			}
			str = strtok(NULL, ":;.");
		}
	}
	return 0;
}

char extract_command(char* meta_data)
{
	char command;
	sscanf(meta_data, "%1s", &command);
	return command;
}

char* extract_operation(char* meta_data)
{
	char *operation, *start, *end;
	remove_spaces(meta_data);
	start = strstr( meta_data, "(" );
	if ( start != NULL )
    {
        start++;
		end = strstr( start, ")" );
        if ( end != NULL )
        {
            operation = (char*)malloc( end - start + 1 );
            memcpy(operation, start, end - start);
            operation[end - start] = '\0';
        }
    }
	if(operation != NULL)
	{
		return operation;
	}
	return NULL;
}

int extract_cycle_time(char* meta_data)
{
	int cycle_time;
	char* start = strstr(meta_data, ")");
	if(start != NULL)
	{
		start++;
		sscanf(start, "%i", &cycle_time);
		return cycle_time;
	}
	return -1;
}