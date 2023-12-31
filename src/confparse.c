#include "confparse.h"



/*
* confparse - small config file parser library, v1.0.3
*
* The confparse project facilitates the process of parsing a configuration 
* file into keys and their corresponding values. These pairs can be handled 
* individually, allowing for easy reading of configuration files. Currently, 
* this project supports up to 500 entries.
*
* Author: Def0x00
* License: MIT
* GitHub Repository: https://github.com/DefNu1l/confparse
*/


static int countlines(const char *filename) {
	int counter = 0;
	char buff[GENBUFF];


	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "configinit :: ERROR :: Unable to open stream for %s\n", 
			filename);
		exit(-1);
	}

	
	while (fgets(buff, GENBUFF, fp) != NULL) {
		if (buff[strlen(buff) - 1] == '\n') {
			buff[strlen(buff) - 1] = '\0';
		}
		if (strlen(buff) == 0 || buff[0] == '#') {
			continue;
		}

		counter++;
	}


	fclose(fp);

	return counter;

}


static void removespace(char *str) {
	char *src = str, *dest = str; 
	

	while (*src != '\0') {
		if (*src != ' ') {
			*dest = *src;
			dest++;
		}
		src++;
	}

	*dest = '\0';
}


static void ignorecomment(char *str) {
	char *pos = strchr(str, '#');
	if (pos != NULL) {
		*pos = '\0';
	}

}



static config_t tokenize(char *line) {
	size_t buff_size = 32;
	char key[buff_size], value[buff_size];
	char *delim = "=";

	strncpy(key, strtok(line, delim), buff_size - 1);
	key[buff_size - 1] = '\0';  

	strncpy(value, strtok(NULL, delim), buff_size - 1);
	value[buff_size - 1] = '\0';	


	removespace(key);
	removespace(value);

	ignorecomment(key);
	ignorecomment(value);

	
	int x = 0, y = 0;


	while (value[x]) {
		if (value[x] != '"') {
			value[y++] = value[x];
		}

		x++;
		
	}
	
	
	value[y] = '\0';

	config_t init;
	init.get_key = strdup(key);
	init.get_value = strdup(value);

	

	return init;
}



static int fileexist(const char *filename) {
	return access(filename, F_OK);
}


static unsigned int issupportedfile(const char *filename) {
	const char *exts[] = {".txt", ".conf", ".ini", ".cfg"};
	const char *ext = strrchr(filename, '.');
	unsigned int supported = 0;

	if (ext != NULL) {
		for (int iter = 0; iter < sizeof(exts) / sizeof(exts[0]); iter++) {
			if (strcmp(ext, exts[iter]) == 0) {
				supported = 1;
				break;
			}
		}

	}


	return supported;

}


int configvalidate(const char *filename, unsigned int verbose) {
	if (verbose != 1 && verbose != 0) {
		fprintf(stderr, "INVALID :: Unknown verbose value set\n");
		return -1;
	}
	else if (verbose == 1) {
		printf("Running validation checks for %s..", filename);
	}


	if (fileexist(filename) != 0) {
		if (verbose == 1) {
			fprintf(stderr, "FATAL :: File %s does not exist\n", filename);
		}
		return -1;
	} 
	if (issupportedfile(filename) == 0) {
		if (verbose == 1) {
			printf("\nINVALID :: File %s cannot be handled\n", filename);
		}
		return -1;

	}


	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		if (verbose == 1) {
			printf("\nINVALID :: Unable to open stream for %s\n", filename);
			
		}
		return -1;
	}
	
	size_t test_buff = GENBUFF + 2;
	char *buff = NULL;
	size_t err = 0;
	while (getline(&buff, &test_buff, fp) != -1) {
		size_t line_length = strlen(buff);
		if (line_length > 0 && buff[line_length - 1] == '\n') {
			line_length--;
		}
		if (line_length > GENBUFF) {
			if (verbose == 1) {
				printf("\nINVALID :: This line is too long: %.20s..\n", buff);
			}
			err++;
			break;
		}
		char *temp = buff;
		while (*temp) {
			if (*temp == '\'' 
				|| (*temp == '/' && *(temp + 1) == '/') 
				|| (*temp == '/' && *(temp + 1) == '*')) {
				if (verbose == 1) {
					printf("\nINVALID :: Only '#' is allowed to mark a comment\n");
				}
				err++;
				break;
			}
			else {
				temp++;
			}

		}


	}


	if (err == 1) {
		return 1;
	}

	fclose(fp);
	free(buff);

	if (countlines(filename) > GENBUFF) {
		if (verbose == 1) {
			printf("\nINVALID :: Too much entries!\n");
		}
		return -1;
	}

	if (verbose == 1) {
		printf("PASSED\n");
	}


	return 0;
}

char *configgetvalue(config_t *session, const char *entry, int count) {
	
	char *value = NULL;
	int hit = 0;

	for (int iter = 0; iter < count; iter++) {
		if (strcmp(session[iter].get_key, entry) == 0) {
			value = session[iter].get_value;
			hit++;
			break;
		}
	}


	if (hit == 0) {
		return NULL;
	}
	


	return value;
}



config_t *configinit(const char *filename, int *count) {
	if (fileexist(filename) != 0) {
		fprintf(stderr, "configinit :: ERROR :: File %s does not exist\n",
			filename);
		exit(-1);

	}
	if (issupportedfile(filename) == 0) {
		fprintf(stderr, "configinit :: ERROR :: Filetype not supported: %s\n", 
			filename);
		exit(-1);

	}
	if (countlines(filename) > GENBUFF) {
		fprintf(stderr, "configinit :: ERROR :: File %s is too large\n",
			filename);
		exit(-1);
	}

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "configinit :: ERROR :: Unable to open stream for %s\n", 
			filename);
		exit(-1);
	}


	config_t *storage = (config_t*)malloc(sizeof(config_t) * GENBUFF); 
	if (storage == NULL) {
		fprintf(stderr, "configinit :: ERROR :: malloc: %s\n", strerror(errno));
		exit(-1);
	}



	int storage_count = 0;
	char buff[GENBUFF];

	while (fgets(buff, GENBUFF, fp) != NULL) {
		if (isspace((unsigned char)*buff) || buff[0] == '#') {
			continue;
		}
		storage[storage_count] = tokenize(buff);
		storage_count++;
	}

	fclose(fp);


	*count = storage_count;
	return storage;
}

void configcleanup(config_t *storage, int count) {
	for (int idx = 0; idx < count; idx++) {
		free(storage[idx].get_key);
		free(storage[idx].get_value);
	}

	free(storage);
}
