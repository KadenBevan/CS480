#include "Process_Parser.h"

static char extract_command(char * meta_data);
static char* extract_operation(char * meta_data);
static int extract_cycle_time(char * meta_data);

int parse_processes(char *filename, Process *process_list)
{
	MetaData meta_list = {-1, '0', "", NULL, NULL};
	meta_datas_to_list(filename, &meta_list);
	int PID = 0;

	while (meta_list.next != NULL)
	{
		MetaData *temp_list = malloc(sizeof(MetaData));
		temp_list->head = NULL;
		temp_list->command = '0';
		temp_list->cycle_time = 0;
		temp_list->operation = "";

		Process *new_process = malloc(sizeof(Process));
		new_process->state = NEW;
		new_process->PID = PID++;
		new_process->total_cycle = 0;
		new_process->operation_list = malloc(sizeof(MetaData));

		while (str_n_cmp(meta_list.operation, "end", 2) != 0)
		{
			if (temp_list->head == NULL)
			{
				temp_list->head = meta_list.head;
				temp_list->command = meta_list.command;
				temp_list->operation = meta_list.operation;
				temp_list->cycle_time = meta_list.cycle_time;
				if (meta_list.command != 'M' && meta_list.command != 'S' && meta_list.command != 'A')
				{
					new_process->total_cycle += meta_list.cycle_time;	// add cycle time
				}
				temp_list->next = NULL;
			}
			else
			{
				MetaData *temp_head = temp_list;
				while (temp_head->next != NULL)
				{
					temp_head = temp_head->next;
				}
				temp_head->next = malloc(sizeof(MetaData));
				temp_head->next->command = meta_list.command;
				temp_head->next->operation = meta_list.operation;
				temp_head->next->cycle_time = meta_list.cycle_time;
				if (meta_list.command != 'M' && meta_list.command != 'S' && meta_list.command != 'A')
				{
					new_process->total_cycle += meta_list.cycle_time;	// add cycle time
				}
				temp_head->next->next = NULL;
			}
			meta_list = *meta_list.next;
		}
		new_process->operation_list = temp_list;
		if (process_list->head == NULL)
		{
			process_list->head = new_process;
			process_list->PID = new_process->PID;
			process_list->state = new_process->state;
			process_list->total_cycle = new_process->total_cycle;
			process_list->operation_list = new_process->operation_list;
			process_list->next = NULL;
		}
		else
		{
			Process *temp_process = process_list;
			while (temp_process->next != NULL)
			{
				temp_process = temp_process->next;
			}
			temp_process->next = new_process;
			temp_process->next->next = NULL;
		}
		meta_list = *meta_list.next;

	}
	return 0;

}

int meta_datas_to_list(char *filename, MetaData *meta_list)
{

	// open file
	FILE* ptr_file;
	if ((ptr_file = fopen(filename, "r")) == NULL)
	{
		return OPEN_FILE_ERROR;
	}
	// get string line
	char line[MAX_STRING];
	char meta_buffer[MAX_STRING];
	int line_index, end_index, start_index, buffer_index, cycle_time;
	char command, *operation;

	while (fgets(line, MAX_STRING, ptr_file) != NULL)
	{
		line_index = 0;
		// if the line does not contain meta-data commands
		if (str_n_cmp(line, "Start Program Meta-Data Code:", 10) == 0
			|| str_n_cmp(line, "End Program Meta-Data Code.", 10) == 0)
		{
			continue;
		}
		// while not the end of the line
		while (*(line + line_index) != 0)
		{
			// if current char is deliminator
			if (*(line + line_index) == ';' || *(line + line_index) == '.')
			{
				// set the end index to current index
				end_index = line_index;
				while (*(line + line_index) != '(')
				{
					line_index--;
				}
				start_index = line_index - 1;
				line_index = end_index;
				for (buffer_index = 0; start_index <= end_index; buffer_index++)
				{
					meta_buffer[buffer_index] = *(line + start_index);
					start_index++;
				}
				meta_buffer[end_index + 1] = '\0';
				command = extract_command(meta_buffer);
				operation = extract_operation(meta_buffer);
				cycle_time = extract_cycle_time(meta_buffer);


				// check data going into node then add node to linked list
				if (is_command(command) == 0 && is_operation(operation) == 0
					&& cycle_time >= 0) 
				{
					MetaData *new_node = malloc(sizeof(MetaData));
					new_node->command = command;
					new_node->cycle_time = cycle_time;
					new_node->operation = operation;
					new_node->next = NULL;
					if (meta_list->head == NULL)
					{
						meta_list->head = new_node;
						meta_list->command = command;
						meta_list->operation = operation;
						meta_list->cycle_time = cycle_time;
					}
					else
					{
						MetaData *temp_head = meta_list;
						while (temp_head->next != NULL)
						{
							temp_head = temp_head->next;
						}
						temp_head->next = new_node;
					}
				}
				else
				{
					fclose(ptr_file);
					return ATTRIBUTE_EXTRACTION_ERROR;
				}
			}
			line_index++;
		}
	}
	fclose(ptr_file);
	return 0;
}

static char extract_command(char* meta_data)
{
	char command;
	int meta_index = 0;
	while (*(meta_data + meta_index) != 0 && is_command(*(meta_data + meta_index)) < 0)
	{
		meta_index++;
	}
	command = *(meta_data + meta_index);
	return command;
}

static char* extract_operation(char* meta_data)
{
	int meta_index = 0, buffer_index;
	char* op_buffer = malloc(sizeof(char) * 15);

	if (op_buffer == NULL)
	{
		return NULL;
	}
	remove_spaces(meta_data);

	while (*(meta_data + meta_index) != 0)
	{
		if (*(meta_data + meta_index) == '(')
		{
			buffer_index = 0;
			meta_index++;
			while (*(meta_data + meta_index) != ')')
			{
				op_buffer[buffer_index] = *(meta_data + meta_index);
				buffer_index++;
				meta_index++;
			}
			*(op_buffer + buffer_index) = '\0';
		}
		meta_index++;
	}
	return op_buffer;
}

static int extract_cycle_time(char* meta_data)
{
	int meta_index = 0, buffer_index;
	char cycle_buffer[SMALL_STRING];

	while (*(meta_data + meta_index) != 0)
	{
		if (*(meta_data + meta_index) == ')')
		{
			buffer_index = 0;
			meta_index++;
			while (*(meta_data + meta_index) != ';' && *(meta_data + meta_index) != '.')
			{
				cycle_buffer[buffer_index] = *(meta_data + meta_index);
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