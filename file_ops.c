#include "shell.h"

/**
 * copy_file - Copies a file from source to destination.
 *
 * @source: Path to the source file to be copied.
 * @destination: Path where the file should be copied to.
 *
 */
void copy_file(const char *source, const char *destination)
{
	char command[MAX_INPUT_SIZE];

	sprintf(command, "cp %s %s", source, destination);
	system(command);
}

/**
* execute_copied_file - Executes a copied file with given arguments.
*
* @file: Path to the copied file that needs to be executed.
* @args: Arguments to pass to the copied file during execution.
*
*/
void execute_copied_file(const char *file, char *args[])
{
	pid_t pid;
	int status;

	 pid = fork();

if (pid == -1)
{
	perror("fork");
	exit(EXIT_FAILURE);
}
if (pid == 0)
{
	execve(file, args, environ);
	perror("execve");
	exit(EXIT_FAILURE);
}

	waitpid(pid, &status, 0);
}
