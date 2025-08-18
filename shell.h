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

/* --- Structure commande --- */
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
