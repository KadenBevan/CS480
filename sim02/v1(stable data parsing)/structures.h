
#ifndef STRUCTURES_H
#define STRUCTURES_H

//Constants
#define MAX_ATTRIBUTE_LENGTH 256

typedef struct ConfigData
{
	int 		version;
	char    	metaFilePath[MAX_ATTRIBUTE_LENGTH];
	int			qTime;
	int			availableMem;
	int			PCT;
	int			IOCT;
	char	    logFilePath[MAX_ATTRIBUTE_LENGTH];
	char 		logTo[MAX_ATTRIBUTE_LENGTH];
	char	 	scheduleCode[MAX_ATTRIBUTE_LENGTH];

} ConfigData;

// payload for linked list Link
typedef struct MetaData
{
	char 		      command;
	char    	      operation[15];
	int 		      cycleTime;
	struct MetaData   *next;

} MetaData;

#endif