#ifndef PROCESS_PARSER
#define PROCESS_PARSER

// ERRORS
#define OPEN_FILE_ERROR -1
#define ATTRIBUTE_EXTRACTION_ERROR -2

#include <stdlib.h>
#include <stdio.h>
#include "Structures.h"
#include "Utility.h"

int parse_processes(char *filename, Process *process_list);
int meta_datas_to_list(char *filename, MetaData *meta_list);

#endif 