#ifndef CONFPARSE_H
#define CONFPARSE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



struct settings {
	char *get_key;
	char *get_value;
};

typedef struct settings init_t;


void removespace(char *str);
init_t tokenize(char *line);
init_t *configinit(const char *filename, int *count);
void configcleanup(init_t *storage, int count);



#endif
