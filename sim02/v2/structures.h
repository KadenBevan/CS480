
#ifndef STRUCTURES_H
#define STRUCTURES_H

//Constants
#define MAX_STRING 256
#define MEDIUM_STRING 128
#define SMALL_STRING 64

typedef struct ConfigData
{
	int version;
	char metaFilePath[MAX_STRING];
	int qTime;
	int availableMem;
	int PCT;
	int IOCT;
	char logFilePath[MAX_STRING];
	char logTo[MAX_STRING];
	char scheduleCode[MAX_STRING];

} ConfigData;

// payload for linked list Link
typedef struct MetaData
{
	char command;
	char operation[SMALL_STRING];
	int cycleTime;

	struct MetaData *next;

} MetaData;

typedef struct FCFSNode
{
	struct PCB* process;
	struct FCFSNode* next;

} FCFSNode;

typedef struct FCFSQueue
{
	struct FCFSNode* head;
	struct FCFSNode* tail;

} FCFSQueue;

typedef struct PCB
{
	struct MetaData *currentAction;
	int PID;
	int cycleTime;

	enum state { NEW, READY, BLOCKED, RUNNING, EXIT } state;
} PCB;

typedef struct ProcessNode
{
	struct PCB* process;

	struct ProcessNode *next;
} ProcessNode;

typedef struct OutputNode
{
	char string[MAX_STRING];

	struct OutputNode* next;
} OutputNode;
#endif
