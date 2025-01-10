#include "shell.h"

/**
 * execute_multiple_times - Executes a command multiple times.
 * @command_path: The full path of the command to execute.
 * @args: The array of arguments for the command.
 * @arg_count: The number of arguments provided.
 */
void execute_multiple_times(char *command_path, char **args, int arg_count)
{
	int repeat_count; /* Number of times the command will be executed. */
	pid_t pid; /* Process ID for the forked processes. */
	int i; /* Counter for the loop. */

	/* Convert the second-to-last argument to an integer for repeat count. */
	repeat_count = atoi(args[arg_count - 2]);

	/* Loop to execute the command 'repeat_count' times. */
	for (i = 0; i < repeat_count; i++)
	{
		pid = fork(); /* Create a new process. */

		if (pid == -1) /* Check if fork failed. */
		{
			perror("fork"); /* Print an error message if fork fails. */
			exit(EXIT_FAILURE); /* Exit the program on critical failure. */
		}

		if (pid == 0) /* Child process block. */
		{
			/* Execute the command using execve. */
			execve(command_path, args, environ);
			perror("execve"); /* Print an error message if execve fails. */
			exit(EXIT_FAILURE); /* Exit the child process on failure. */
		}

		/* Parent process waits for the child process to finish. */
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
	/*Check if the input matches the format: "Copy the file <source> to <dest>*/
	return (arg_count > 5 &&
			strcmp(args[0], "Copy") == 0 &&
			strcmp(args[1], "the") == 0 &&
			strcmp(args[2], "file") == 0);
}

/**
 * handle_copy_command - Handles the copy and execution of a file command.
 * @args: The array of arguments for the copy command.
 */
void handle_copy_command(char **args)
{
	char *new_args[3]; /* Array for arguments to execute the copied file. */

	/* Copy the file from source (args[3]) to destination (args[5]). */
	copy_file(args[3], args[5]);

	/* Prepare arguments for executing the copied file. */
	new_args[0] = args[5]; /* The copied file becomes the command to execute. */
	new_args[1] = "/var"; /* Placeholder argument. */
	new_args[2] = NULL; /* Null-terminate the arguments array. */

	/* Execute the copied file with the prepared arguments. */
	execute_copied_file(args[5], new_args);
}

/**
 * execute_single_command - Executes a single command normally.
 * @command_path: The full path of the command to execute.
 * @args: The array of arguments for the command.
 */
void execute_single_command(char *command_path, char **args)
{
	pid_t pid; /* Process ID for the forked process. */

	pid = fork(); /* Create a new process. */

	if (pid == -1) /* Check if fork failed. */
	{
		perror("fork"); /* Print an error message if fork fails. */
		exit(EXIT_FAILURE); /* Exit the program on critical failure. */
	}

	if (pid == 0) /* Child process block. */
	{
		/* Execute the command using execve. */
		execve(command_path, args, environ);
		perror("execve failed"); /* Print an error message if execve fails. */
		exit(EXIT_FAILURE); /* Exit the child process on failure. */
	}

	/* Parent process waits for the child process to finish. */
	waitpid(pid, NULL, 0);
}
