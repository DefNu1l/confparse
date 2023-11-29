# confparse - Small configuration file parsing library. 

The confparse project facilitates the process of parsing a configuration file into keys and their corresponding values. These pairs can be handled individually, allowing for easy reading of configuration files. Currently, this project supports up to 100 entries.

### Usage

- To use confparse, both the source and header files must be included in the current project. Since it is not a header-only project, confparse.c must be included in the Makefile as well.

```C
#include "path/to/confparse.h"
```

- The following functions are available to handle a config file:

```C
// Load the config file and define the number of entries
init_t *configinit(const char *filename, int *count);

// Free memory allocated by the configinit function
void configcleanup(init_t *storage, int count);
```

- The keys and their values are managed through an index. Here is an example of how the functions can be used (test.c):

```C
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
```

- Note: confparse is currently at the `beginning` of its development.

### License

The confparse project has been released under the [MIT](https://github.com/DefNu1l/confparse/blob/main/LICENSE) License.
