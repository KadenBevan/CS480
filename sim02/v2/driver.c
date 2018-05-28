#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "structures.h"
#include "linkedlist.h"
#include "dataProcessor.h"
#include "utility.h"
#include "processhandler.h"
#include "simtimer.h"



int main(int argc, char* argv[])
{
	// check args
	if (argc != 2)
	{
		printf("Command line argument error!\n");
		return -1;
	}
	char* config_path = argv[1];
	// setup linked list
	LinkedList *meta_data_list = NULL;
	meta_data_list = list_create();

	int extract_error = 0;
	ConfigData configData = { -1, "", -1, -1, -1, -1, "", "", "" };

	// var to hold time
	char timestr[SMALL_STRING];
	accessTimer(0, timestr);
	
	// linked list of strings
	OutputNode output_head = { "", NULL };
	char output_line[MAX_STRING];

	// put string into output line
	accessTimer(1, timestr);
	sprintf(output_line, "Time: %9s, System Start\n", timestr);

	// add output to list
	add_output(output_line, &output_head);

	// clear the output line
	output_line[0] = '\0';

	// parse meta-data file and config file. fill structs. check for errors.
	extract_error = parse_data(config_path, &configData, meta_data_list);
	if (extract_error == CONFIG_EXTRACT_ERROR)
	{
		printf("Config file extraction error!\n");
		return -1;
	}
	if (extract_error == META_EXTRACT_ERROR)
	{
		printf("Meta-Data file extraction error!\n");
		return -1;
	}

	accessTimer(1, timestr);
	sprintf(output_line, "Time: %9s, OS: Begin PCB Creation\n", timestr);
	add_output(output_line, &output_head);
	output_line[0] = '\0';

	// set up a PCB list
	ProcessNode process_list = { NULL, NULL };
	meta_to_pcb_list(meta_data_list, &process_list, &configData);

	accessTimer(1, timestr);
	sprintf(output_line, "Time: %9s, OS: All processes initialized in New state\n", timestr);
	add_output(output_line, &output_head);
	output_line[0] = '\0';

	// setup ready queue
	FCFSQueue ready_queue = { NULL, NULL };

	if (str_n_cmp(configData.scheduleCode, "FCFS-N", 5) == 0)
	{
		fill_fcfsn(&ready_queue, &process_list);

		accessTimer(1, timestr);
		sprintf(output_line, "Time: %9s, OS: All processes now set in Ready state\n", timestr);
		add_output(output_line, &output_head);
		output_line[0] = '\0';

		PCB* pnext;
		while ((pnext = next_process(&ready_queue, "FCFS-N")) != NULL)
		{
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, OS: FCFS-N Strategy selects Process %i with time: %i mSec\n", timestr, pnext->PID, pnext->cycleTime);
			add_output(output_line, &output_head);
			output_line[0] = '\0';
			
			run(pnext, &output_head, timestr);

		}
		accessTimer(1, timestr);
		sprintf(output_line, "Time: %9s, OS: System stop\n", timestr);
		add_output(output_line, &output_head);
		output_line[0] = '\0';
		
	}
	
	int p1_return, p2_return;
	pthread_t pthread_file_output;
	pthread_t pthread_monitor_output;
	
	
	if(str_n_cmp(configData.logTo, "File", 3) == 0)
	{
		struct arg_struct args;
		args.head = &output_head;
		args.filepath = configData.logFilePath;
		p1_return = pthread_create( &pthread_file_output, NULL, output_file, (void*) &args);
		pthread_join(pthread_file_output, NULL);
	}
	if(str_n_cmp(configData.logTo, "Monitor", 6) == 0)
	{
		p2_return = pthread_create( &pthread_monitor_output, NULL, output_monitor, (void*) &output_head);
		pthread_join(pthread_monitor_output, NULL);
	}
	else if(str_n_cmp(configData.logTo, "Both", 3) == 0)
	{
		p1_return = pthread_create( &pthread_file_output, NULL, output_file, (void*) &output_head);
		p2_return = pthread_create( &pthread_monitor_output, NULL, output_monitor, (void*) &output_head);
		pthread_join(pthread_monitor_output, NULL);
		pthread_join(pthread_file_output, NULL);
	}
	
    
	
	//print_output(&output_head);

	list_distroy(meta_data_list);
	return 0;
}
