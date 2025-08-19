#include "shell.h"

/* Pointeur global vers la ligne lue */
char *global_input = NULL; 

/**
 * sigint_handler - Handle SIGINT signal
 * @sig: Signal number
 *
 * Return: void
 */
void sigint_handler(int sig)
{
    (void)sig;
    if (global_input)
	{
        free(global_input);   /* libère la mémoire allouée pour la ligne */
		global_input = NULL;
	}
    write(STDOUT_FILENO, "\n", 1);
    builtin_exit();           /* exécute la fonction exit propre */
    _exit(0);                 /* quitte immédiatement le processus */
}
