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
		exit(EXIT_SUCCESS); /* Exit the shell */

	if (strcmp(args[0], "env") == 0)
	{
		print_env(); /* Print environment variables */
		return;
	}
	command_path = get_command_path(args); /* Get the command path */
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		free(command_path);
		return;
	}
	if (is_multiple_execution(args, arg_count))
	{
		execute_multiple_times(command_path, args, arg_count);
		free(command_path); /* Free allocated command path memory */
		return;
	}
	if (is_copy_command(args, arg_count))
	{
		handle_copy_command(args); /* Handle copying and executing a file */
		free(command_path); /* Free allocated command path memory */
		return;
	}
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

	return (arg_count); /* Return number of arguments tokenized */
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
		return (args[0]); /* Use absolute path directly */

	return (get_location(args[0])); /* Search in PATH for command location */
}

/**
 * is_multiple_execution - Checks if the command should be executed
 * @args: The array of arguments.
 * @arg_count: The number of arguments.
 *
 * Return: 1 if multiple execution is required, 0 otherwise.
 */
int is_multiple_execution(char **args, int arg_count)
{
	/* Check if the last argument is "times" and there are enough arguments. */
	return (arg_count > 2 && strcmp(args[arg_count - 1], "times") == 0);
}
