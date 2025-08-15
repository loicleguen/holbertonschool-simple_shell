#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>

typedef struct shell {
    char command;
    int (*handler)(va_list args);
} shell_t;

ssize_t read_line(char **line, size_t *len);
void parse_line(char *line, char *argv[]);
void execute_command(char *argv[]);
int (*which_handler(const char *format, int i2))(va_list);

#endif /* SHELL_H */
