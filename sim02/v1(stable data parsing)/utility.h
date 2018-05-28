#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"

void remove_spaces(char* source);
int is_command(char command);
int is_operation(char* operation);
int is_config(ConfigData* config_data);
int str_cmp(char* s1, char* s2);
int a_to_i(char* str);

#endif