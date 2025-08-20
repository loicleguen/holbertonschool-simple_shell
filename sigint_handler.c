#include "shell.h"

/**
 * sigint_handler - Handles the SIGINT signal (Ctrl+C)
 * @sig: The signal number
 */
void sigint_handler(int sig)
{
	(void)sig;
	if (global_input)
		write(STDOUT_FILENO, "\n#LFG$ ", 7);
}
