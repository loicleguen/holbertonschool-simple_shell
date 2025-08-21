#include "shell.h"

/**
 * run_non_interactive - Executes commands in non-interactive mode
 */
void run_non_interactive(void)
{
	size_t buffer_size = 0;
	ssize_t chars_read;
	command_t cmd;

	while ((chars_read = read_command(&global_input, &buffer_size, 0)) != -1)
	{
		if (chars_read > 0 && global_input[chars_read - 1] == '\n')
			global_input[chars_read - 1] = '\0';

		if (global_input[0] == '\0')
			continue;
		cmd.line = global_input;
		cmd.args = parse_command(cmd.line);
		if (!cmd.args)
		{
			perror("./shell");
			continue;
		}
		if (_strcmp(cmd.args[0], "exit") == 0)
		{
			free_args(cmd.args);
			break;
		}
		if (_strcmp(cmd.args[0], "env") == 0)
		{
			builtin_env();
			free_args(cmd.args);
			continue;
		}
		execute_command(cmd);
		free_args(cmd.args);
	}
	free(global_input);
	global_input = NULL;
}
