#include "../src/confparse.h"


int main(void) {

	int storage_count;
	init_t *storage = configinit("test.txt", &storage_count);

	for (int idx = 0; idx < storage_count; idx++) {
		printf("KEY: %s\nVALUE: %s\n",
			storage[idx].get_key, storage[idx].get_value);
	}

	configcleanup(storage, storage_count);

	return 0;
}
