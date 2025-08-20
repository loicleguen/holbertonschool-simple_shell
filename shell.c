#include "shell.h"

/**
 * read_command - Read a line from stdin
 * @input: Pointer to buffer that stores user input
 * @bufsize: Pointer to size of allocated buffer
 * @is_interactive: Flag, 1 if interactive mode
 *
 * Return: Number of characters read, or -1 on EOF/error
 */
ssize_t read_command(char **input, size_t *bufsize, int is_interactive)
{
	ssize_t chars_read;

	if (is_interactive)
		write(STDOUT_FILENO, PROMPT, _strlen(PROMPT));

	chars_read = getline(input, bufsize, stdin);

	if (chars_read == -1 && is_interactive)
		write(STDOUT_FILENO, "\n", 1);

	return (chars_read);
}

/**
 * parse_command - Tokenize a command line into arguments
 *                - Tokeniser une ligne de commande en arguments
 * @line: Command line to parse / Ligne de commande à analyser
 *
 * Return: Pointer to NULL-terminated array of arguments
 *         Pointeur vers un tableau d'arguments terminé par NULL
 */
char **parse_command(char *line)
{
	char **args = NULL;
	char *token;
	size_t count = 0;
	char *delim = " \t\n";

	char *line_copy;

	line_copy = _strdup(line);
	if (!line_copy)
		return (NULL);

	token = strtok(line_copy, delim);

	while (token)
	{
		count++;
		token = strtok(NULL, delim);
	}
	free(line_copy);

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	count = 0;
	token = strtok(line, delim);
	while (token)
	{
		args[count++] = token;
		token = strtok(NULL, delim);
	}
	args[count] = NULL;

	return (args);
}

/**
 * execute_command - Fork and execute a command
 *                  - Forker et exécuter une commande
 * @cmd: Command structure containing the command line
 *       Structure commande contenant la ligne à exécuter
 *
 * Return: 0 on success, -1 on failure
 *         0 en cas de succès, -1 en cas d'échec
 */
int execute_command(command_t cmd)
{
	pid_t child_pid;
	int status;
	char *resolved_path;

	resolved_path = find_command_in_path(cmd.args[0]);
	if (!resolved_path)
	{
		fprintf(stderr, "./shell: %s: command not found\n", cmd.args[0]);
		return (-1);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("./shell");
		free(resolved_path);
		return (-1);
	}
	if (child_pid == 0)
	{
		cmd.args[0] = resolved_path;
		if (execve(resolved_path, cmd.args, environ) == -1)
		{
			perror("./shell");
			_exit(127);
		}
	}
	else
	{
		if (waitpid(child_pid, &status, 0) == -1)
			perror("./shell");
	}
	free(resolved_path);
	return (0);
}

/**
 * find_command_in_path - Search for a command in the PATH
 *                        - Rechercher une commande dans le PATH
 * @command: Command to find / Commande à rechercher
 *
 * Return: Full path to the command or NULL
 *         Chemin complet vers la commande ou NULL
 */
char *find_command_in_path(char *command)
{
	char *path_env, *path_copy, *dir;
	char full_path[1024];

	if (_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (_strdup(command));
		else
			return (NULL);
	}
	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = _strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (_strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * main - Entry point of the simple shell
 *       - Point d'entrée du mini-shell
 *
 * Return: Always 0
 *         Toujours 0
 */
int main(void)
{
	char *input = NULL;
	size_t buffer_size = 0;
	ssize_t chars_read;
	int is_interactive;
	command_t cmd;

	is_interactive = isatty(STDIN_FILENO);
	while (1)
	{
		chars_read = read_command(&input, &buffer_size, is_interactive);
		if (chars_read == -1)
			break;
		if (chars_read > 0 && input[chars_read - 1] == '\n')
			input[chars_read - 1] = '\0';
		if (input[0] == '\0')
			continue;
		cmd.line = input;
		cmd.args = parse_command(cmd.line);
		if (!cmd.args)
		{
			perror("./shell");
			continue;
		}
		if (_strcmp(cmd.args[0], "exit") == 0)
		{
			free(cmd.args);
			free(input);
			exit(0);
		}
		if (_strcmp(cmd.args[0], "env") == 0)
		{
			builtin_env();
			free(cmd.args);
			continue;
		}
		execute_command(cmd);
		free(cmd.args);
	}
	free(input);
	return (0);
}
