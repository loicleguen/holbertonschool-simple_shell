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
		write(STDOUT_FILENO, PROMPT, _strlen(PROMPT));

	/* Read user input / Lire l'entrée utilisateur */
	chars_read = getline(input, bufsize, stdin);

	/* Handle EOF (Ctrl+D) / Gérer EOF (Ctrl+D) */
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

	line_copy = strdup(line);
	if (!line_copy)
	return (NULL);

	/* First pass: count number of arguments / Compter le nombre d'arguments */
	token = strtok(line_copy, delim);

	while (token)
	{
		count++;
		token = strtok(NULL, delim);
	}
	free(line_copy);


	/* Allocate array of pointers / Allouer le tableau de pointeurs */
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);

	/* Second pass: store arguments / Stocker les arguments */
	count = 0;
	token = strtok(line, delim); /* Reset strtok / Recommencer strtok */
	while (token)
	{
		args[count++] = token;
		token = strtok(NULL, delim);
	}
	args[count] = NULL; /* Null-terminated / Terminé par NULL */

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
		free(resolved_path);
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

    /* Si la commande contient un '/' → chemin absolu ou relatif */
	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
		return (strdup(command)); /* On retourne tel quel */
		else
		return (NULL); /* Fichier inexécutable ou introuvable */
	}

    /* Sinon, on cherche dans le PATH */
path_env = getenv("PATH");
if (!path_env)
	return (NULL);

path_copy = strdup(path_env);
	if (!path_copy)
	return (NULL);

dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
			if (access(full_path, X_OK) == 0)
			{
				free(path_copy);
				return (strdup(full_path));
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
		/* Parse command into arguments / Tokeniser la ligne en arguments */
		cmd.args = parse_command(cmd.line);
		if (!cmd.args)
		{
			perror("./shell");
			continue;
		}
		/* Execute command / Exécuter la commande */
		execute_command(cmd);
		free(cmd.args); /* Free arguments array / Libérer le tableau d'arguments */
	}
	/* Free memory before exit / Libérer la mémoire avant de quitter */
	free(input);
	return (0);
}
