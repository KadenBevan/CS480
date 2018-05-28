#include "Output_Handler.h"

static void output_monitor(OutputNode *output_head);
static void output_file(OutputNode *output_head, char *filepath);

void handle_output(Config *config, OutputNode *output)
{
	if (str_n_cmp(config->logTo, "Both", 3) == 0)
	{
		output_file(output, config->logFilePath);
		output_monitor(output);
	}
	else if (str_n_cmp(config->logTo, "Monitor", 3) == 0)
	{
		output_monitor(output);
	}
	else if (str_n_cmp(config->logTo, "File", 3) == 0)
	{
		output_file(output, config->logFilePath);
	}
}

void output_monitor(OutputNode *output_head)
{
	OutputNode *out_ptr = output_head;
	while (out_ptr != NULL)
	{
		printf("%s", out_ptr->string);
		out_ptr = out_ptr->next;
	}
	return;
}

void output_file(OutputNode *output_head, char *filepath)
{
	OutputNode *out_ptr = output_head;
	FILE* logfile;
	if ((logfile = fopen(filepath, "w")) == NULL)
	{
		return;
	}
	while (out_ptr != NULL)
	{
		fputs(out_ptr->string, logfile);
		out_ptr = out_ptr->next;
	}
}
