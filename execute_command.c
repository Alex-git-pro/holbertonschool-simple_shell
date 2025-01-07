#include "main.h"

/**
 * execute_command - Executes a command entered by the user.
 * @prog_name: Name of the program (used for error messages).
 * @line: Command string.
 * Return: 0 on success, 1 on failure.
 */
int execute_command(char *prog_name, char *line)
{
    char **args;
    int status = 0;

    /* Tokenize the input line */
    args = tokenize_line(line);
    if (!args || !args[0])
    {
        free(args);
        return (status);
    }

    /* Check if the command is a built-in */
    if (_strcmp(args[0], "exit") == 0)
    {
        exit_shell(args);
    }
    else if (_strcmp(args[0], "cd") == 0)
    {
        cd_builtin(args);
    }
    else if (_strcmp(args[0], "ls") == 0)
    {
        ls_builtin(args);
    }
    else
    {
        /* Attempt to execute the command */
        if (fork() == 0)
        {
            if (execve(args[0], args, NULL) == -1)
            {
                perror(prog_name);
                free(args);
                exit(1);
            }
        }
        else
        {
            wait(NULL);
        }
    }

    free(args);
    return (status);
}
