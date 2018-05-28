#include "Scheduler.h"

int schedule_jobs(Config *configuration, Process *jobs_list, OutputNode *output, char *timestr)
{
	Process *job_ptr = jobs_list;
	OutputNode *output_ptr = output;
	char output_line[MAX_STRING];

	if (str_n_cmp(configuration->scheduleCode, "FCFS-N", 4) == 0)
	{

		while (job_ptr != NULL)
		{
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, OS: FCFS-N Strategy selects Process %i with time: %i mSec\n", timestr, job_ptr->PID, job_ptr->total_cycle);
			add_output(output_line, output);
			output_line[0] = '\0';
			run_process(job_ptr, configuration->IOCT, configuration->PCT, output_ptr, timestr);
			job_ptr = job_ptr->next;
		}
	}
	if (str_n_cmp(configuration->scheduleCode, "FCFS-P", 4) == 0)
	{

		while (job_ptr != NULL)
		{
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, OS: FCFS-N Strategy selects Process %i with time: %i mSec\n", timestr, job_ptr->PID, job_ptr->total_cycle);
			add_output(output_line, output);
			output_line[0] = '\0';
			run_process(job_ptr, configuration->IOCT, configuration->PCT, output_ptr, timestr);
			job_ptr = job_ptr->next;
		}
	}
	if (str_n_cmp(configuration->scheduleCode, "SJF-N", 2) == 0)
	{
		int process_count = 0, counter = 0;
		while (job_ptr->next != NULL)
		{
			process_count++;
			job_ptr = job_ptr->next;
		}
		job_ptr = jobs_list;
		int shortest = 999999;
		Process *process;
		while (counter < process_count) 
		{
			while (job_ptr != NULL)
			{
				if (job_ptr->total_cycle < shortest && job_ptr->state != EXIT)
				{
					shortest = job_ptr->total_cycle;
					process = job_ptr;
				}
				job_ptr = job_ptr->next;
			}
			job_ptr = jobs_list;
			counter++;
			shortest = 999999;
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, OS: SJF Strategy selects Process %i with time: %i mSec\n", timestr, process->PID, process->total_cycle);
			add_output(output_line, output);
			output_line[0] = '\0';
			run_process(process, configuration->IOCT, configuration->PCT, output_ptr, timestr);
		}
	}
	if (str_n_cmp(configuration->scheduleCode, "SJF-P", 2) == 0)
	{
		int process_count = 0, counter = 0;
		while (job_ptr->next != NULL)
		{
			process_count++;
			job_ptr = job_ptr->next;
		}
		job_ptr = jobs_list;
		int shortest = 999999;
		Process *process;
		while (counter < process_count) 
		{
			while (job_ptr != NULL)
			{
				if (job_ptr->total_cycle < shortest && job_ptr->state != EXIT)
				{
					shortest = job_ptr->total_cycle;
					process = job_ptr;
				}
				job_ptr = job_ptr->next;
			}
			job_ptr = jobs_list;
			counter++;
			shortest = 999999;
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, OS: SJF Strategy selects Process %i with time: %i mSec\n", timestr, process->PID, process->total_cycle);
			add_output(output_line, output);
			output_line[0] = '\0';
			run_process(process, configuration->IOCT, configuration->PCT, output_ptr, timestr);
		}
	}
	if (str_n_cmp(configuration->scheduleCode, "RR-P", 2) == 0)
	{
		int process_count = 0, counter = 0;
		while (job_ptr->next != NULL)
		{
			process_count++;
			job_ptr = job_ptr->next;
		}
		job_ptr = jobs_list;
		int shortest = 999999;
		Process *process;
		while (counter < process_count) 
		{
			while (job_ptr != NULL)
			{
				if (job_ptr->total_cycle < shortest && job_ptr->state != EXIT)
				{
					shortest = job_ptr->total_cycle;
					process = job_ptr;
				}
				job_ptr = job_ptr->next;
			}
			job_ptr = jobs_list;
			counter++;
			shortest = 999999;
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, OS: SJF Strategy selects Process %i with time: %i mSec\n", timestr, process->PID, process->total_cycle);
			add_output(output_line, output);
			output_line[0] = '\0';
			run_process(process, configuration->IOCT, configuration->PCT, output_ptr, timestr);
		}
	}
	if (str_n_cmp(configuration->scheduleCode, "SRTF-P", 2) == 0)
	{
		int process_count = 0, counter = 0;
		while (job_ptr->next != NULL)
		{
			process_count++;
			job_ptr = job_ptr->next;
		}
		job_ptr = jobs_list;
		int shortest = 999999;
		Process *process;
		while (counter < process_count) 
		{
			while (job_ptr != NULL)
			{
				if (job_ptr->total_cycle < shortest && job_ptr->state != EXIT)
				{
					shortest = job_ptr->total_cycle;
					process = job_ptr;
				}
				job_ptr = job_ptr->next;
			}
			job_ptr = jobs_list;
			counter++;
			shortest = 999999;
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, OS: SJF Strategy selects Process %i with time: %i mSec\n", timestr, process->PID, process->total_cycle);
			add_output(output_line, output);
			output_line[0] = '\0';
			run_process(process, configuration->IOCT, configuration->PCT, output_ptr, timestr);
		}
	}
	return 0;
}
