#include "shell.h"

/**
 * execute_command - Executes the given command with arguments.
 * @input: The full command line input.
 */
void execute_command(char *input)
{
    char *args[MAX_INPUT_SIZE / 2 + 1]; /* Array to hold tokenized arguments */
    char *command_path; /* Full path of the command */
    int arg_count;

    arg_count = tokenize_input(input, args); /* Tokenize input into arguments */

    if (arg_count == 0)
        return; /* Handle empty input */

    if (strcmp(args[0], "exit") == 0)
    {
        exit(EXIT_SUCCESS); /* Exit the shell */
    }

    if (strcmp(args[0], "env") == 0)
    {
        print_env(); /* Print environment variables */
        return;
    }

    command_path = get_command_path(args); /* Get the command path */
    if (command_path == NULL)
    {
        fprintf(stderr, "%s: command not found\n", args[0]); /* Command not found error */
        return;
    }

    /* Handle multiple executions */
    if (is_multiple_execution(args, arg_count))
    {
        execute_multiple_times(command_path, args, arg_count); /* Execute command multiple times */
        free(command_path); /* Free allocated command path memory */
        return;
    }

    /* Handle copy and execute case */
    if (is_copy_command(args, arg_count))
    {
        handle_copy_command(args); /* Handle copying and executing a file */
        free(command_path); /* Free allocated command path memory */
        return;
    }

    /* Default execution for a single command */
    execute_single_command(command_path, args); /* Execute a single command */
}

/**
 * tokenize_input - Tokenizes the input string into arguments.
 * @input: The input string to tokenize.
 * @args: The array to store tokenized arguments.
 *
 * Return: The number of arguments tokenized.
 */
int tokenize_input(char *input, char **args)
{
    char *token; /* Pointer for tokenized strings */
    int arg_count = 0; /* Number of arguments tokenized */

    token = strtok(input, " "); /* Tokenize based on spaces */

    while (token != NULL && arg_count < MAX_INPUT_SIZE / 2)
    {
        args[arg_count] = token; /* Store token in args array */
        arg_count++;
        token = strtok(NULL, " "); /* Get next token */
    }
    
    args[arg_count] = NULL; /* Null-terminate the array */

    return arg_count; /* Return number of arguments tokenized */
}

/**
 * get_command_path - Retrieves the full path of a command.
 * @args: The array of arguments containing the command.
 *
 * Return: Full path of the command or NULL if not found.
 */
char *get_command_path(char **args)
{
    if (args[0][0] == '/')
        return args[0]; /* Use absolute path directly */

    return get_location(args[0]); /* Search in PATH for command location */
}

/**
 * is_multiple_execution - Checks if the command should be executed multiple times.
 * @args: The array of arguments.
 * @arg_count: The number of arguments.
 *
 * Return: 1 if multiple execution is required, 0 otherwise.
 */
int is_multiple_execution(char **args, int arg_count)
{
    return (arg_count > 2 && strcmp(args[arg_count - 1], "times") == 0); 
}

/**
 * execute_multiple_times - Executes a command multiple times.
 * @command_path: The full path of the command to execute.
 * @args: The array of arguments for the command.
 * @arg_count: The number of arguments provided.
 *
 */ 
void execute_multiple_times(char *command_path, char **args, int arg_count)
{
    int repeat_count; 
    pid_t pid; 
    int i; 

    repeat_count = atoi(args[arg_count - 2]); 

    for (i = 0; i < repeat_count; i++)
    {
        pid = fork(); 

        if (pid == -1) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0) 
        {
            execve(command_path, args, environ); 
            perror("execve");
            exit(EXIT_FAILURE);
        }
        
        waitpid(pid, NULL, 0); 
    }
}

/**
 * is_copy_command - Checks if the input is a copy command.
 * @args: The array of arguments.
 * @arg_count: The number of arguments provided.
 *
 * Return: 1 if it's a copy command, 0 otherwise.
 */ 
int is_copy_command(char **args, int arg_count)
{
   return (arg_count > 5 && strcmp(args[0], "Copy") == 0 && 
           strcmp(args[1], "the") == 0 && strcmp(args[2], "file") == 0); 
}

/**
 * handle_copy_command - Handles the copy and execution of a file command.
 * @args: The array of arguments for the copy command.
 *
 */ 
void handle_copy_command(char **args)
{
   char *new_args[3]; 
   copy_file(args[3], args[5]); 

   new_args[0] = args[5]; 
   new_args[1] = "/var"; 
   new_args[2] = NULL; 

   execute_copied_file(args[5], new_args); 
}

/**
 * execute_single_command - Executes a single command normally.
 * @command_path: The full path of the command to execute.
 * @args: The array of arguments for the command.
 *
 */ 
void execute_single_command(char *command_path, char **args)
{
   pid_t pid; 

   pid = fork(); 

   if (pid == -1) 
   {
       perror("fork");
       exit(EXIT_FAILURE);
   }
   
   if (pid == 0) 
   {
       execve(command_path, args, environ); 
       perror("execve failed");
       exit(EXIT_FAILURE);
   }
   
   waitpid(pid, NULL, 0); 
}
