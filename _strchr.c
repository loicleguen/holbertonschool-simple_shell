#include "shell.h"

/**
 * _strchr - Locates a character in a string
 * @str: The string to search
 * @c: The character to find
 *
 * Return: Pointer to the first occurrence of c in str, or NULL if not found
 */
char *_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}

	if (c == '\0')
		return ((char *)str);
		
	return (NULL);
}
