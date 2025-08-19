#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: char
 * Return: Always (n) result
 */

int _strlen(char *s)
{
	int n;

	for (n = 0; s[n] != 0; n++)
		;
	return (n);
}
