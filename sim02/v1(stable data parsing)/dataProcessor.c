#include "dataProcessor.h"

void print_data(ConfigData* config_data, LinkedList* list)
{
	// print config_data
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

	// check list and set up head node
	if (list == NULL)
	{
		return;
	}
	MetaData *head = list->head;

	// print meta_data linked list
	while (head != NULL)
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
	// call extract config data with params from driver
	extract_config(fn_config, config_data);

	// check config_data is filled correctly
	if (is_config(config_data) == 0)
	{
		// return the 0 if extract_meta_data is successfull
		return extract_meta_data(config_data->metaFilePath, list);
	}
	else
		return ATTRIBUTE_EXTRACTION_ERROR;
}

int extract_config(char* fn_config, ConfigData* config_data)
{
	// open config file for reading and check success
	FILE* fh = fopen(fn_config, "r");
	if (fh == NULL)
	{
		return OPEN_FILE_ERROR;
	}

	// set up line for fgets function
	char line[MAX_ATTRIBUTE_LENGTH];

	// for every line in the config file
	while (fgets(line, MAX_ATTRIBUTE_LENGTH, fh) != NULL)
	{
		int error = 0;
		// try every possible attribute on each config line
		error += sscanf(line, "Version/Phase: %i", &config_data->version);
		error += sscanf(line, "File Path: %255s", config_data->metaFilePath);
		error += sscanf(line, "CPU Scheduling Code: %255s", config_data->scheduleCode);
		error += sscanf(line, "Quantum Time (cycles): %i", &config_data->qTime);
		error += sscanf(line, "Memory Available (KB): %i", &config_data->availableMem);
		error += sscanf(line, "Processor Cycle Time (msec): %i", &config_data->PCT);
		error += sscanf(line, "I/O Cycle Time (msec): %i", &config_data->IOCT);
		error += sscanf(line, "Log To: %255s", config_data->logTo);
		error += sscanf(line, "Log File Path: %255s", config_data->logFilePath);
	}
	fclose(fh);
	return 0;
}

int extract_meta_data(char* fp_meta_data, LinkedList* list)
{
	// open file
	FILE* fh = fopen(fp_meta_data, "r");
	if (fh == NULL)
	{
		return OPEN_FILE_ERROR;
	}
	// get string line
	char line[MAX_ATTRIBUTE_LENGTH];
	char meta_buffer[MAX_ATTRIBUTE_LENGTH];
	int line_index = 0, end_index, start_index, buffer_index, cycle_time;
	char command, *operation;
	while (fgets(line, MAX_ATTRIBUTE_LENGTH, fh) != NULL)
	{
		line_index = 0;
		// if the line does not contain meta-data commands
		if (str_cmp(line, "Start Program Meta-Data Code:\n") == 0
			|| str_cmp(line, "End Program Meta-Data Code.") == 0)
		{
			continue;
		}
		// while not the end of the line
		while (line[line_index] != 0)
		{
			// if current char is deliminator
			if (line[line_index] == ';' || line[line_index] == '.')
			{
				// set the end index to current index
				end_index = line_index;
				while (line[line_index] != '(')
				{
					line_index--;
				}
				start_index = line_index - 1;
				line_index = end_index;
				for (buffer_index = 0; start_index <= end_index; buffer_index++)
				{
					meta_buffer[buffer_index] = line[start_index];
					start_index++;
				}
				meta_buffer[end_index + 1] = '\0';
				command = extract_command(meta_buffer);
				operation = extract_operation(meta_buffer);
				cycle_time = extract_cycle_time(meta_buffer);
				// check data going into node
				if (is_command(command) == 0 && is_operation(operation) == 0
					&& cycle_time >= 0) {
					MetaData *newNode = (MetaData*)malloc(sizeof(MetaData));
					if (newNode == NULL)
					{
						return ATTRIBUTE_EXTRACTION_ERROR;
					}
					newNode = list_create_node(command, operation, cycle_time);
					insert_node(list, newNode);
				}
			}
			line_index++;
		}
	}
	return 0;
}

char extract_command(char* meta_data)
{
	char command;
	int meta_index = 0;
	while (meta_data[meta_index] != 0 && is_command(meta_data[meta_index]) < 0)
	{
		meta_index++;
	}
	command = meta_data[meta_index];
	return command;
}

char* extract_operation(char* meta_data)
{
	int meta_index = 0, buffer_index;
	char* op_buffer = malloc(sizeof(char)*15);

	if (op_buffer == NULL)
	{
		return NULL;
	}
	remove_spaces(meta_data);

	while (meta_data[meta_index] != 0)
	{
		if (meta_data[meta_index] == '(')
		{
			buffer_index = 0;
			meta_index++;
			while (meta_data[meta_index] != ')')
			{
				op_buffer[buffer_index] = meta_data[meta_index];
				buffer_index++;
				meta_index++;
			}
			op_buffer[buffer_index] = '\0';
		}
		meta_index++;
	}
	return op_buffer;
}

int extract_cycle_time(char* meta_data)
{
	int meta_index = 0, buffer_index;
	char cycle_buffer[10];

	while (meta_data[meta_index] != 0)
	{
		if (meta_data[meta_index] == ')')
		{
			buffer_index = 0;
			meta_index++;
			while (meta_data[meta_index] != ';' && meta_data[meta_index] != ':')
			{
				cycle_buffer[buffer_index] = meta_data[meta_index];
				buffer_index++;
				meta_index++;
			}
			cycle_buffer[buffer_index] = '\0';
		}
		meta_index++;
	}
	int ret = a_to_i(cycle_buffer);
	return ret;
}