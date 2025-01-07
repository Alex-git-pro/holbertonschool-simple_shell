#ifndef MAIN_H
#define MAIN_H
/*---MACROS---*/
#define TOK_BUFF_SIZE 64
#define TOK_DELIM " \t\r\n\a"
extern char **environ;
/*---LIBRARIES---*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
/*---PROTOTYPES---*/
void shell_interactive(void);
void shell_no_interactive(void);
char *read_line(void);
char **split_line(char *line);
char *read_stream(void);
int execute_args(char **args);
int ocd(char **args);
int oexit(char **args);
int ohelp(char **args);
int oenv(char **args);
char *get_env(const char *name);
int try_exec(char **args);
int new_process(char **args);


#endif
