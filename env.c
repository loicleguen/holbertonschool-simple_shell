#include "shell.h"

/**
* builtin_env - prints the current environment variables
*/
void builtin_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
