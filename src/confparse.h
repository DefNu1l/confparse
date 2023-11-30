#ifndef CONFPARSE_H
#define CONFPARSE_H


/*
* confparse - small config file parser library, v1.0.1
*
* This is the header file for confparse.c
*
* Author: Def0x00
* License: MIT
* GitHub Repository: https://github.com/DefNu1l/confparse
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>


#define GENBUFF 512


struct settings {
	char *get_key;
	char *get_value;
};

typedef struct settings init_t;



int countlines(const char *filename);
void ignorecomment(char *str);


int configvalidate(const char *filename, unsigned int verbose);


void removespace(char *str);
init_t tokenize(char *line);
init_t *configinit(const char *filename, int *count);
void configcleanup(init_t *storage, int count);



#endif
