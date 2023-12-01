#ifndef CONFPARSE_H
#define CONFPARSE_H


/*
* confparse - small config file parser library, v1.0.3
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
#include <unistd.h>

#define GENBUFF 512


struct settings {
	char *get_key;
	char *get_value;
};

typedef struct settings config_t;


int configvalidate(const char *filename, unsigned int verbose);
config_t *configinit(const char *filename, int *count);
void configcleanup(config_t *storage, int count);
char *configgetvalue(config_t *session, const char *entry, int count);


#endif
