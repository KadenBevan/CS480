#ifndef STRUCTURES_H
#define STRUCTURES_H

//Constants
#define MAX_STRING 256
#define MEDIUM_STRING 128
#define SMALL_STRING 64

typedef struct Config
{
	int version;
	int qTime;
	int availableMem;
	int PCT;
	int IOCT;
	char logFilePath[MAX_STRING];
	char logTo[MAX_STRING];
	char scheduleCode[MAX_STRING];
	char metaFilePath[MAX_STRING];

} Config;

typedef struct Process
{
	int PID;
	enum state {NEW, READY, BLOCKED, RUNNING, EXIT} state;
	int total_cycle;

	struct MetaData *operation_list;
	struct Process *head;
	struct Process *next;
} Process;

typedef struct MetaData
{
	int cycle_time;
	char command;
	char* operation;

	struct MetaData *head;
	struct MetaData *next;
} MetaData;

typedef struct OutputNode
{
	char string[MAX_STRING];
	struct OutputNode* next;
} OutputNode;

struct arg_struct {
	int time;
};

#endif