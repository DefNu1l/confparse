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
config_t *configinit(const char *filename, int *count);

// Extract the value of a specific key
char *configgetvalue(config_t *session, const char *entry, int count);

// Free memory allocated by the configinit function
void configcleanup(config_t *storage, int count);
```

#### Details:
`configvalidate`

Parameters:
- `filename`: config file which needs to be checked
- `verbose`: verbose mode, 1 to enable messages and 0 to hide

Description:

The configvalidate function checks the file for required formats like commenting, size and type.

Return value:

configvalidate will return `-1` when any check fails and `0` when no issues where detected.

`configinit`

Parameters:
- `filename`: config file to load
- `count`: number of entries (lines) set in `filename`

Description:

configinit can be used to load the actual config file and also checks for some issues when `configvalidate` isn't called (BUT IT IS RECOMMENDED!). It is the most important function which will tokenize the entries and perform various handles.

Return value:

On success, configinit returns a pointer to an array of structs containing the `key` and the `value` of the current entry. If it fails, it will print a message to stderr with a hint to the failure.


`configgetvalue`

Parameters:
- `session`: pointer to loaded session
- `entry`: key to get the value from
- `count`: number of entries (lines)


Description:

configgetvalue will query the value in the main array to find the corresponding value. When the entry is found, it will return the value.

Return value:

If the call fails, configgetvalue returns NULL. Otherwise, the value of the specified entry is returned.


`configcleanup`

Parameters:
- `storage`: pointer to the previous defined array of structs
- `count`: expected number of entries (lines) for iterate to free  

Description:

`configinit` will allocate memory for the current structure and returns a pointer to it. This `needs to be freed` and the configcleanup function is used to free the previous allocated memory when there is no need anymore.


### Example
- The keys and their values are managed through an index. Here is an example of how the functions can be used (test.c):

```C
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

```

- The config file pattern currently supported is:
```
# Comments can be defined using a hashtag
# Configurations File for . . . 
# Description . . .
# Last edited . . . 

ip = "127.0.0.1" # ip address set to localhost
port = 5003 # standard port 
dns="8.8.8.8" # spaces does not matter 
```

#### Note 

confparse is in its early stages of development.
If you encounter any issues or have suggestions for improvements, please feel free to let me know. Your feedback is valuable as we work towards enhancing and refining the functionality of confparse. Thank you for your support!


### License

The confparse project has been released under the [MIT](https://github.com/DefNu1l/confparse/blob/main/LICENSE) License.
