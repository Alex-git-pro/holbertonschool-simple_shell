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
    int source_fd;
    int dest_fd;
    ssize_t bytes_read;
    ssize_t bytes_written;
    char buffer[1024];


    source_fd = open(source, O_RDONLY);
    if (source_fd == -1) 
    {
        perror("Error opening source file");
        return;
    }


    dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) 
    {
        perror("Error opening destination file");
        close(source_fd);
        return;
    }


    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) 
    {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written == -1) 
        {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return;
        }
    }

    if (bytes_read == -1) 
    {
        perror("Error reading source file");
    }

    close(source_fd);
    close(dest_fd);
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
	perror("execve failed");
	exit(EXIT_FAILURE);
}

	waitpid(pid, &status, 0);
}
