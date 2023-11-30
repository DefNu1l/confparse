#include "../src/confparse.h"


int main(void) {

	const char *config_file = "test.txt";
	

	int check = configvalidate(config_file, 0);
	if (check != 1) {
		int storage_count;
		init_t *storage = configinit(config_file, &storage_count);

		for (int idx = 0; idx < storage_count; idx++) {
			printf("KEY: %s\nVALUE: %s\n",
				storage[idx].get_key, storage[idx].get_value);
		}

		configcleanup(storage, storage_count);
	}
	else {
		puts("Check failed");
		return -1;
	}

	return 0;
}
