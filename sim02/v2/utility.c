#include "utility.h"

void remove_spaces(char* source)
{
	char* place = source;
	char* origin = source;
	while (*origin != 0)
	{
		*place = *origin++;
		if (*place != ' ')
			place++;
	}
	*place = '\0';
}

int is_config(ConfigData* config_data)
{
	int error = 0;
	if (config_data->version > 10 || config_data->version < 0)
	{
		error++;
	}
	else if (config_data->qTime < 0 || config_data->qTime > 100)
	{
		error++;
	}
	else if (config_data->availableMem < 0 || config_data->availableMem > 1048576)
	{
		error++;
	}
	else if (config_data->PCT < 0 || config_data->PCT > 1000)
	{
		error++;
	}
	else if (config_data->IOCT < 0 || config_data->IOCT > 10000)
	{
		error++;
	}
	else if (config_data->metaFilePath == NULL)
	{
		error++;
	}
	else if (config_data->logFilePath == NULL)
	{
		error++;
	}
	else if (config_data->logTo == NULL)
	{
		error++;
	}
	else if (config_data->scheduleCode == NULL)
	{
		error++;
	}
	return error;
}

int is_command(char command)
{
	if (command == 'S' || command == 'A' || command == 'P'
		|| command == 'M' || command == 'I' || command == 'O')
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int is_operation(char* operation)
{
	if (str_n_cmp(operation, "start", 4)
		|| str_n_cmp(operation, "allocate", 7)
		|| str_n_cmp(operation, "harddrive", 8)
		|| str_n_cmp(operation, "run", 2)
		|| str_n_cmp(operation, "keyboard", 7)
		|| str_n_cmp(operation, "monitor", 6)
		|| str_n_cmp(operation, "access", 5)
		|| str_n_cmp(operation, "printer", 6)
		|| str_n_cmp(operation, "end", 2))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int str_n_cmp(const char* string1, const char* string2, size_t size)
{
	while (size && *string1 && (*string1 == *string2))
	{
		++string1;
		++string2;
		--size;
	}
	if (size == 0)
	{
		return 0;
	}
	else
	{
		// cast to unsigned char because it is safer
		return (*(unsigned char *)string1 - *(unsigned char *)string2);
	}
}

int a_to_i(char* str)
{
	int new_int = 0, index;

	for (index = 0; str[index] != '\0'; index++)
	{
		new_int = new_int * 10 + str[index] - '0';
	}
	return new_int;
}

int add_output(char* new_str, OutputNode* head)
{
	if (str_n_cmp(head->string, "", 1) == 0)
	{
		strcpy(head->string, new_str);
		head->next = NULL;
	}
	else
	{
		OutputNode* new_node = malloc(sizeof(OutputNode));
		new_node->next = NULL;
		while (head->next != NULL)
		{
			head = head->next;
		}
		head->next = new_node;
		strcpy(head->next->string, new_str);
	}
	return 0;
}

void* output_monitor(void* head)
{
	struct OutputNode *node;
    node = ( struct OutputNode * )head;

	while (node != NULL)
	{
		printf("%s", node->string);
		node = node->next;
	}
	pthread_exit(NULL);
	return NULL;
}

void* output_file(void* arguments)
{
	struct OutputNode *node;
	struct arg_struct *args = arguments;
    node = ( struct OutputNode * )args->head;
	
	FILE* logfile;	
	if ((logfile = fopen(args->filepath, "w")) == NULL)
	{
		pthread_exit(NULL);
		return NULL;
	}
	while (node != NULL)
	{
		fputs(node->string, logfile);
		node = node->next;
	}
	pthread_exit(NULL);
    return NULL;
}