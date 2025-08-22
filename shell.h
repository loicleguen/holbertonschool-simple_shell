#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

#define PROMPT "#LFG$ "

extern char **environ;
extern char *global_input;

/**
 * struct command_s - Structure representing a command with arguments
 * @line: Raw command line entered by the user
 * @args: Array of arguments including command name, NULL-terminated
 */
typedef struct command_s
{
	char *line;
	char **args;
} command_t;

int main(void);
ssize_t read_command(char **input, size_t *bufsize, int is_interactive);
char **parse_command(char *line);
int execute_command(command_t cmd);
char *find_command_in_path(char *command);
void builtin_env(void);
void builtin_exit(void);
void run_interactive(void);
void run_non_interactive(void);
void sigint_handler(int sig);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_getenv(const char *name);
char *_strchr(const char *str, int c);
void free_args(char **args);

#endif /* SHELL_H */
