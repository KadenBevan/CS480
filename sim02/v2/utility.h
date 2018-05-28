#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "structures.h"

void remove_spaces(char* source);
int is_command(char command);
int is_operation(char* operation);
int is_config(ConfigData* config_data);
int str_n_cmp(const char* s1, const char* s2, size_t size);
int a_to_i(char* str);
int add_output(char* new_str, OutputNode* head);

// threads

struct arg_struct {
    void* head;
    char* filepath;
};

void* output_file(void* head);
void* output_monitor(void* head);
#endif
