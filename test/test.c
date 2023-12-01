#include "../src/confparse.h"


int main(void) {

	const char *config_file = "test.txt"; // Config file
	

	int check = configvalidate(config_file, 0); // Run a validation check
	if (check != 1) {
		int storage_count; // Number of entries in config_file
		// Load the config file and tokenize the entries
		config_t *storage = configinit(config_file, &storage_count);

		// Iterate over the number of entries and extract the current key and value
		for (int idx = 0; idx < storage_count; idx++) {
			printf("KEY: %s\nVALUE: %s\n",
				storage[idx].get_key, storage[idx].get_value);
		}


		char *value = configgetvalue(storage, "test", storage_count);
		if (value == NULL) {
			// Free allocated memory when configgetvalue does not found the entry
			configcleanup(storage, storage_count);
			fprintf(stderr, "Entry not found!\n");
			return -1;
		}


		printf("%s\n", value);

		// Free allocated memory by the configinit function
		configcleanup(storage, storage_count);
	}
	else {
		// Config file validation cannot be approved
		fprintf(stderr, "Check failed!\n");
		return -1;
	}

	return 0;
}
