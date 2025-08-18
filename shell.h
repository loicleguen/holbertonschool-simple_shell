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
} command_t;


#endif /* SHELL_H */
