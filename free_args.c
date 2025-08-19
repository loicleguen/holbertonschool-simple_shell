#include "shell.h"

/**
 * free_args - Libère un tableau d'arguments
 * @args: Le tableau d'arguments à libérer
 */
void free_args(char **args)
{
	size_t i = 0;

	if (!args)
		return;
	while (args[i])
		free(args[i++]);
	free(args);
}
