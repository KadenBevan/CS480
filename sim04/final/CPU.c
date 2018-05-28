#include "CPU.h"

int run_process(Process *process, int IOCT, int PCT, OutputNode *output, char *timestr)
{
	process->state = RUNNING;
	char output_line[MAX_STRING];
	sprintf(output_line, "Time: %9s, Process %i set in Running state\n", timestr, process->PID);
	add_output(output_line, output);
	output_line[0] = '\0';

	MetaData *tasks = process->operation_list;
	while (tasks->next != NULL)
	{
		run_task(tasks, process, IOCT, PCT, output, timestr);
		tasks = tasks->next;
	}
	// process set in EXIT state
	process->state = EXIT;
	
	accessTimer(1, timestr);
	sprintf(output_line, "Time: %9s, Process %i set in Exit state\n", timestr, process->PID);
	add_output(output_line, output);
	output_line[0] = '\0';
	return 0;
}

int run_task(MetaData *task, Process *process, int IOCT, int PCT, OutputNode *output, char *timestr)
{
	// process set in RUNNING STATE
	pthread_t thread;
	char output_line[MAX_STRING];
	if(task->command == 'I')
	{
		accessTimer(1, timestr);
		sprintf(output_line, "Time: %9s, Process %i, %s input start\n", timestr, process->PID, task->operation);
		add_output(output_line, output);
		output_line[0] = '\0';
		
		process->state = BLOCKED;
		int arg = task->cycle_time * IOCT;
		pthread_create(&thread, NULL, sleep_runner, (void *) arg);
		pthread_join(thread, NULL);
		process->state = READY;
		
		accessTimer(1, timestr);
		sprintf(output_line, "Time: %9s, Process %i, %s input end\n", timestr, process->PID, task->operation);
		add_output(output_line, output);
		output_line[0] = '\0';
	}
	if(task->command == 'O')
	{
		accessTimer(1, timestr);
		sprintf(output_line, "Time: %9s, Process %i, %s output start\n", timestr, process->PID, task->operation);
		add_output(output_line, output);
		output_line[0] = '\0';
		
		process->state = BLOCKED;
		int arg = task->cycle_time * IOCT;
		pthread_create(&thread, NULL, sleep_runner, (void *) arg);
		pthread_join(thread, NULL);
		process->state = READY;
		
		accessTimer(1, timestr);
		sprintf(output_line, "Time: %9s, Process %i, %s output end\n", timestr, process->PID, task->operation);
		add_output(output_line, output);
		output_line[0] = '\0';
	}
	if (task->command == 'M')
	{
		int original, segment, base, allocation;
		original = task->cycle_time;
		segment = original / 1000000;
		base = (original - (segment * 1000000))/1000;
		allocation = original - ((segment * 1000000) + (base * 1000));
		if (str_n_cmp(task->operation, "allocate", 4) == 0)
		{
			char output_line[MAX_STRING];
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, OS: Process %i, MMU Allocation: %i/%i/%i start\n", timestr, process->PID, segment, base, allocation);
			add_output(output_line, output);
			output_line[0] = '\0';
			// call MMU
			if (allocate_memory(segment, base, allocation) == 0)
			{
				accessTimer(1, timestr);
				sprintf(output_line, "Time: %9s, OS: Process %i, MMU Allocation: Successful\n", timestr, process->PID);
				add_output(output_line, output);
				output_line[0] = '\0';
			}
			else
			{
				accessTimer(1, timestr);
				sprintf(output_line, "Time: %9s, OS: Process %i, MMU Allocation: Failed\n", timestr, process->PID);
				add_output(output_line, output);
				output_line[0] = '\0';
				
				accessTimer(1, timestr);
				sprintf(output_line, "Time: %9s, OS: Process %i, Segmentation Fault - Process ended\n", timestr, process->PID);
				add_output(output_line, output);
				output_line[0] = '\0';
			}
		}
		else if (str_n_cmp(task->operation, "access", 4) == 0)
		{
			char output_line[MAX_STRING];
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, OS: Process %i, MMU Access: %i/%i/%i start\n", timestr, process->PID, segment, base, allocation);
			add_output(output_line, output);
			output_line[0] = '\0';
			// call MMU
			if (access_memory(segment, base, allocation) == 0)
			{
				accessTimer(1, timestr);
				sprintf(output_line, "Time: %9s, OS: Process %i, MMU Access: Successful\n", timestr, process->PID);
				add_output(output_line, output);
				output_line[0] = '\0';
			}
			else
			{
				accessTimer(1, timestr);
				sprintf(output_line, "Time: %9s, OS: Process %i, MMU Allocation: Failed\n", timestr, process->PID);
				add_output(output_line, output);
				output_line[0] = '\0';
			}
		}
	}
	else
	{
		accessTimer(1, timestr);
		sprintf(output_line, "Time: %9s, Process %i, %s operation start\n", timestr, process->PID, task->operation);
		add_output(output_line, output);
		output_line[0] = '\0';
		
		int runtime = task->cycle_time * PCT;
		runTimer(runtime);
		
		accessTimer(1, timestr);
		sprintf(output_line, "Time: %9s, Process %i, %s operation end\n", timestr, process->PID, task->operation);
		add_output(output_line, output);
		output_line[0] = '\0';
	}
	return 0;
}
