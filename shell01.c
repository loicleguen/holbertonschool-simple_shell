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

	/* Show prompt if in interactive mode */
	/* Afficher le prompt si mode interactif */
	if (is_interactive)
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

	/* Read user input / Lire l'entrée utilisateur */
	chars_read = getline(input, bufsize, stdin);

	/* Handle EOF (Ctrl+D) / Gérer EOF (Ctrl+D) */
	if (chars_read == -1 && is_interactive)
		write(STDOUT_FILENO, "\n", 1);

	return (chars_read);
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
	char *args[] = {cmd.line, NULL}; /* Only one argument / Un seul argument */

	/* Create child process / Créer un processus enfant */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("./shell"); /* Fork failed / Fork a échoué */
		return (-1);
	}

	/* Child process / Processus enfant */
	if (child_pid == 0)
	{
		/* Try to execute command / Essayer d'exécuter la commande */
		if (execve(cmd.line, args, environ) == -1)
		{
			perror("./shell"); /* Exec failed / Exec a échoué */
			_exit(127);       /* Exit with error code / Quitter avec code d'erreur */
		}
	}
	else
	{
		/* Parent process waits for child / Le parent attend l'enfant */
		if (waitpid(child_pid, &status, 0) == -1)
			perror("./shell");
	}

	return (0);
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
	char *input = NULL;     /* Buffer for input / Buffer pour l'entrée */
	size_t buffer_size = 0; /* Size of buffer / Taille du buffer */
	ssize_t chars_read;     /* Number of chars read / Nombre de caractères lus */
	int is_interactive;     /* Interactive flag / Indicateur interactif */
	command_t cmd;          /* Command structure / Structure commande */

	/* Check if running in interactive mode */
	/* Vérifier si on est en mode interactif */
	is_interactive = isatty(STDIN_FILENO);

	/* Main shell loop / Boucle principale du shell */
	while (1)
	{
		chars_read = read_command(&input, &buffer_size, is_interactive);
		if (chars_read == -1) /* EOF (Ctrl+D) or error / EOF (Ctrl+D) ou erreur */
			break;

		/* Remove trailing newline / Supprimer le retour à la ligne */
		if (chars_read > 0 && input[chars_read - 1] == '\n')
			input[chars_read - 1] = '\0';

		/* Skip empty input / Ignorer entrée vide */
		if (input[0] == '\0')
			continue;

		/* Store command in structure / Stocker commande dans la structure */
		cmd.line = input;

		/* Execute command / Exécuter la commande */
		execute_command(cmd);
	}

	/* Free memory before exit / Libérer la mémoire avant de quitter */
	free(input);
	return (0);
}
