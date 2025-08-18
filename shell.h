#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

/* --- Constante du prompt --- */
#define PROMPT "#cisfun$ "
/* --- Variables globales --- */
extern char **environ;

/**
 * struct command_s - Structure that represents a command with arguments
 *                   - Structure qui représente une commande avec arguments
 * @line: Raw command line entered by the user
 *        Ligne brute saisie par l'utilisateur
 * @args: Array of arguments including command name, NULL-terminated
 *        Tableau d'arguments incluant le nom de la commande, terminé par NULL
 */
typedef struct command_s
{
	char *line;   /* La ligne saisie par l'utilisateur */
	char **args;  /* Les arguments de la commande */
} command_t;

ssize_t read_command(char **input, size_t *bufsize, int is_interactive);
char **parse_command(char *line);
int execute_command(command_t cmd);
int main(void);

#endif /* SHELL_H */
