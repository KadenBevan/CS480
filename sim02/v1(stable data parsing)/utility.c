#include "utility.h"

void remove_spaces(char* source)
{
	char* i = source;
	char* j = source;
	while (*j != 0)
	{
		*i = *j++;
		if (*i != ' ')
			i++;
	}
	*i = '\0';
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
	if (str_cmp(operation, "start")
		|| str_cmp(operation, "allocate")
		|| str_cmp(operation, "harddrive")
		|| str_cmp(operation, "run")
		|| str_cmp(operation, "keyboard")
		|| str_cmp(operation, "monitor")
		|| str_cmp(operation, "access")
		|| str_cmp(operation, "printer")
		|| str_cmp(operation, "end"))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int str_cmp(char* s1, char* s2)
{
	if (s1 == NULL || s2 == NULL)
	{
		return -1;
	}
	char *ptr_s1 = s1;
	char *ptr_s2 = s2;
	int index;
	for (index = 0; ptr_s1[index] != '\0' && ptr_s2[index] != '\0'; index++)
	{
		// cast memory location ptr_s# + index to an unsigned char
		// check if they are different
		if ((unsigned char*)(ptr_s1 + index) > (unsigned char*)(ptr_s2 + index)
			|| (unsigned char*)(ptr_s1 + index) < (unsigned char*)(ptr_s2 + index))
		{
			return -1;
		}
	}
	return 0;
}

int a_to_i(char* str)
{
	int new_int = 0;

	for (int i = 0; str[i] != '\0'; i++)
	{
		new_int = new_int * 10 + str[i] - '0';
	}
	return new_int;
}