#include "shell.h"

/**
 * free_args - Libère un tableau d'arguments
 * @args: Le tableau d'arguments à libérer
 */
void free_args(char **args)
{
	if (args)
		free(args);
}
