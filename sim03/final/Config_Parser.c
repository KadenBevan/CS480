#include "Config_Parser.h"

int parse_config(char *filename, Config *config_data)
{
	// open config file for reading and check success
	FILE* ptr_file;
	if ((ptr_file = fopen(filename, "r")) == NULL)
	{
		return OPEN_FILE_ERROR;
	}
	// set up line for fgets function
	char line[MAX_STRING];
	// for every line in the config file
	while (fgets(line, sizeof(line), ptr_file) != NULL)
	{
		// try every possible attribute on each config line
		if (strncmp(line, "Version/Phase:", 10) == 0)
		{
			sscanf(line, "Version/Phase: %d", &config_data->version);
		}
		if (strncmp(line, "File Path:", 7) == 0)
		{
			char temp_file[MEDIUM_STRING];
			sscanf(line, "File Path: %s", temp_file);
			strcpy(config_data->metaFilePath, temp_file);
		}
		if (strncmp(line, "CPU Scheduling Code:", 15) == 0)
		{
			char temp_code[MEDIUM_STRING];
			sscanf(line, "CPU Scheduling Code: %s", temp_code);
			strcpy(config_data->scheduleCode, temp_code);
		}
		if (strncmp(line, "Quantum Time (cycles):", 18) == 0)
		{
			sscanf(line, "Quantum Time (cycles): %d", &config_data->qTime);
		}
		if (strncmp(line, "Memory Available (KB):", 18) == 0)
		{
			sscanf(line, "Memory Available (KB): %d", &config_data->availableMem);
		}
		if (strncmp(line, "Processor Cycle Time (msec):", 20) == 0)
		{
			sscanf(line, "Processor Cycle Time (msec): %d", &config_data->PCT);
		}
		if (strncmp(line, "I/O Cycle Time (msec):", 15) == 0)
		{
			sscanf(line, "I/O Cycle Time (msec): %d", &config_data->IOCT);
		}
		if (strncmp(line, "Log To:", 5) == 0)
		{
			char temp_logto[MEDIUM_STRING];
			sscanf(line, "Log To: %s", temp_logto);
			strcpy(config_data->logTo, temp_logto);
		}
		if (strncmp(line, "Log File Path:", 10) == 0)
		{
			char temp_logpath[MEDIUM_STRING];
			sscanf(line, "Log File Path: %s", temp_logpath);
			strcpy(config_data->logFilePath, temp_logpath);
		}
	}
	fclose(ptr_file);
	return is_config(config_data);
}

// check memory time as per spec
int memory_check(int memory)
{
	if(memory >= 0 && memory <= 1048576)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// check pct time as per spec
int pct_check(int pct)
{
	if(pct >= 1 && pct <= 1000)
	{
		return 1;
	}
	else
	{
		return -1;		
	}
}

// check ioct time as per spec
int ioct_check(int ioct)
{
	if(ioct >= 1 && ioct <= 10000)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// check quantum time as per spec
int quantum_check(int quantum)
{
	if(quantum >= 0 && quantum <= 100)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}