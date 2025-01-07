#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

/* Function prototypes */
int main(int argc, char **argv);
int execute_command(char *prog_name, char *line);
char **tokenize_line(char *line);
int _strcmp(char *s1, char *s2);
void exit_shell(char **args);
void cd_builtin(char **args);
int ls_builtin(char **args);

#endif
