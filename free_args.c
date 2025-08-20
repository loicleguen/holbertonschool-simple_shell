#include "shell.h"

/**
 * free_args - Frees a NULL-terminated array of strings
 * @args: The array of strings to free
 */
void free_args(char **args)
{
	if (args)
		free(args);
}
