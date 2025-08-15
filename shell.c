#include "shell.h"

#define MAX_ARGS 64
#define PROMPT "Our_simple_shell$ "

/**
 * read_line - Displays prompt and reads input
 * @line: pointer to buffer
 * @len: pointer to buffer size
 *
 * Return: number of characters read, -1 on EOF/error
 */
ssize_t read_line(char **line, size_t *len)
{
	printf(PROMPT);
	fflush(stdout);
	return (getline(line, len, stdin));
}

/**
 * parse_line - Splits a command line into arguments
 * @line: command line string
 * @argv: array to store arguments
 */
void parse_line(char *line, char *argv[])
{
	char *token;
	int i = 0;

	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';

	token = strtok(line, " ");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
}

/**
 * execute_command - Forks and runs a command
 * @argv: array of arguments
 */
void execute_command(char *argv[])
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return;
	}
	if (child_pid == 0)
	{
		execvp(argv[0], argv);
		perror("execvp");
		_exit(1);
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - Entry point of the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv[MAX_ARGS];

	while (1)
	{
		nread = read_line(&line, &len);
		if (nread == -1)
		{
			printf("\n");
			break;
		}

		parse_line(line, argv);

		if (argv[0] == NULL) /* Empty input */
			continue;

		execute_command(argv);
	}

	free(line);
	return (0);
}
