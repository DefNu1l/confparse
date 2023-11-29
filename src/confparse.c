#include "confparse.h"



void removespace(char *str) {
    char *t = str;
    do {
        if(*t != ' ') {
            *str++ = *t;
	}
    } while(*t++ != '\0');
}


init_t tokenize(char *line) {
	size_t buff_size = 32;
	char key[buff_size], value[buff_size];
	char *delim = "=";

	
	strcpy(key, strtok(line, delim));
	strcpy(value, strtok(NULL, delim));
	
	removespace(key);
	removespace(value);

	
	int x = 0, y = 0;

	while (value[x]) {
		if (value[x] != '"') {
			value[y++] = value[x];
		}

		x++;
		
	}
	
	
	value[y] = '\0';

	init_t init;
	init.get_key = strdup(key);
	init.get_value = strdup(value);

	

	return init;
}


init_t *configinit(const char *filename, int *count) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "configinit :: ERROR :: Unable to open stream for %s\n", 
			filename);
		exit(-1);
	}

	
	size_t buff_size = 100;

	init_t *storage = (init_t*)malloc(sizeof(init_t) * buff_size); 
	if (storage == NULL) {
		fprintf(stderr, "configinit :: ERROR :: malloc: %s\n", strerror(errno));
		exit(-1);
	}



	int storage_count = 0;
	char buff[buff_size];

	while (fgets(buff, buff_size, fp) != NULL) {
		storage[storage_count] = tokenize(buff);
		storage_count++;
	}

	fclose(fp);


	*count = storage_count;
	return storage;
}

void configcleanup(init_t *storage, int count) {
	for (int idx = 0; idx < count; idx++) {
		free(storage[idx].get_key);
		free(storage[idx].get_value);
	}

	free(storage);
}

