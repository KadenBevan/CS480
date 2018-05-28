#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "linkedlist.h"
#include "utility.h"

// ERRORS

#define OPEN_FILE_ERROR -1
#define ATTRIBUTE_EXTRACTION_ERROR -2
#define CONFIG_EXTRACT_ERROR -3
#define META_EXTRACT_ERROR -4

//functions

void print_data(ConfigData* config_data, LinkedList* list);
int parse_data(char* fn_config, ConfigData* config_data, LinkedList* list);
int extract_config(char* fn_config, ConfigData* config_data);
int extract_meta_data(char* fp_meta_data, LinkedList* list);
char extract_command(char* meta_data);
char* extract_operation(char* meta_data);
int extract_cycle_time(char* meta_data);
int is_config(ConfigData* config_data);

#endif
