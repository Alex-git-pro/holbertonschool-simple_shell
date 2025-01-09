#include "shell.h"

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
