# confparse - Small configuration file parsing library. 

The confparse project facilitates the process of parsing a configuration file into keys and their corresponding values. These pairs can be handled individually, allowing for easy reading of configuration files. Currently, this project supports up to 500 entries.

### Usage

- To use confparse, both the source and header files must be included in the current project. Since it is not a header-only project, confparse.c must be included in the Makefile as well.

```C
#include "path/to/confparse.h"
```

- The following functions are available to handle a config file:

```C
// Validate config file
int configvalidate(const char *filename, unsigned int verbose);

// Load the config file and define the number of entries
init_t *configinit(const char *filename, int *count);

// Free memory allocated by the configinit function
void configcleanup(init_t *storage, int count);
```

#### Details:
`configvalidate`

Description:

The configvalidate function checks the file for required formats like commenting, size and type.

Return value:

configvalidate will return `-1` when any check fails and `0` when no issues where detected.

`configinit`

Description:

configinit can be used to load the actual config file and also checks for some issues when `configvalidate` isn't called (BUT IT IS RECOMMENDED!). It is the most important function which will tokenize the entries and perform various handles.

Return value:

On success, configinit returns a pointer to an array of structs containing the `key` and the `value` of the current entry. If it fails, it will print a message to stderr with a hint to the failure.


`configcleanup`

Description:

`configinit` will allocate memory for the current structure and returns a pointer to it. The configcleanup function is used to free the previous allocated memory when there is no need anymore.


### Example
- The keys and their values are managed through an index. Here is an example of how the functions can be used (test.c):

```C
#include "../src/confparse.h"


int main(void) {

	const char *config_file = "test.txt"; // Config file
	

	int check = configvalidate(config_file, 1); // Run a validation check
	if (check != 1) {
		int storage_count; // Number of entries in config_file
		// Load the config file and tokenize the entries
		init_t *storage = configinit(config_file, &storage_count);

		// Iterate over the number of entries and extract the current key and value
		for (int idx = 0; idx < storage_count; idx++) {
			printf("KEY: %s\nVALUE: %s\n",
				storage[idx].get_key, storage[idx].get_value);
		}

		// Free allocated memory by the configinit function
		configcleanup(storage, storage_count);
	}
	else {
		// Config file validation cannot be approved
		puts("Check failed");
		return -1;
	}

	return 0;
}
```

#### Note 

confparse is currently at the `beginning` of its development.
If you encounter any issues or have suggestions for improvements, please feel free to let me know. Your feedback is valuable as we work towards enhancing and refining the functionality of confparse. Thank you for your support!


### License

The confparse project has been released under the [MIT](https://github.com/DefNu1l/confparse/blob/main/LICENSE) License.
