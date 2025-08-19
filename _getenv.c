#include "shell.h"

/**
 * _getenv - retrieves the value of an environment variable
 * @name: name of the variable (e.g. "PATH")
 *
 * Return: pointer to the value string, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t len = strlen(name);

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (environ[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}
