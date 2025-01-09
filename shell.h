#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024

extern char **environ;

/* Function prototypes */
void execute_command(char *input);
void print_env(void);
char *get_location(char *command);
void copy_file(const char *source, const char *destination);
void execute_copied_file(const char *file, char *args[]);
int tokenize_input(char *input, char **args);
char *get_command_path(char **args);
int is_multiple_execution(char **args, int arg_count);
void execute_multiple_times(char *command_path, char **args, int arg_count);
int is_copy_command(char **args, int arg_count);
void handle_copy_command(char **args);
void execute_single_command(char *command_path, char **args);

#endif /* SHELL_H */
