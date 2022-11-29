#ifndef _LIST_H_
#define _LIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************MACROS FOR TEMPLATE FILE****************************/

#define MAX_LINES 50
#define MAX_VARS 10
#define MAX_LINE_LEN 100
#define MAX_DATA_ROWS 20

/******************************MACROS FOR DATA FILE*******************************/

#define  MAX_VAR_LEN 40
#define MAX_NAME_LEN MAX_VAR_LEN
#define MAX_VALUE_LEN MAX_VAR_LEN

#define BUFFER_SIZE 100
#define FILE_SIZE 200

/************************SUCCESS FAILURE EXECUTIONS********************************/

#define FAILURE 0
#define SUCCESS 1

/**********************FUNCTION DECLARTION********************************************/

void replace(char *str,const char *old_word,const char *new_word);
int load_template_file(char *filename);
int extract_tokens(char *line,char row[MAX_VARS][MAX_VAR_LEN]);
int load_data_file(char *filename);
void process_replacements();

#endif
