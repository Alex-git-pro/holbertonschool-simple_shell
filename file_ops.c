#include "shell.h"

/**
 * copy_file - Copies a file from source to destination.
 *
 * @source: Path to the source file to be copied.
 * @destination: Path where the file should be copied to.
 */
void copy_file(const char *source, const char *destination)
{
    int source_fd; /* File descriptor for the source file. */
    int dest_fd; /* File descriptor for the destination file. */
    ssize_t bytes_read; /* Number of bytes read from the source file. */
    ssize_t bytes_written; /* Number of bytes written to the destination file. */
    char buffer[1024]; /* Buffer to temporarily store data during copying. */

    /* Open the source file in read-only mode. */
    source_fd = open(source, O_RDONLY);
    if (source_fd == -1) /* Check if opening the source file failed. */
    {
        perror("Error opening source file"); /* Print an error message. */
        return; /* Exit the function if the source file cannot be opened. */
    }

    /* Open or create the destination file in write mode. */
    dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) /* Check if opening the destination file failed. */
    {
        perror("Error opening destination file"); /* Print an error message. */
        close(source_fd); /* Close the source file to free resources. */
        return; /* Exit the function if the destination file cannot be opened. */
    }

    /* Loop to read data from the source file and write it to the destination file. */
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0)
    {
        /* Write the data read into the destination file. */
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written == -1) /* Check if writing to the destination file failed. */
        {
            perror("Error writing to destination file"); /* Print an error message. */
            close(source_fd); /* Close the source file. */
            close(dest_fd); /* Close the destination file. */
            return; /* Exit the function on write failure. */
        }
    }

    if (bytes_read == -1) /* Check if the last read operation failed. */
    {
        perror("Error reading source file"); /* Print an error message. */
    }

    /* Close both the source and destination files after copying is complete. */
    close(source_fd);
    close(dest_fd);
}

/**
 * execute_copied_file - Executes a copied file with given arguments.
 *
 * @file: Path to the copied file that needs to be executed.
 * @args: Arguments to pass to the copied file during execution.
 */
void execute_copied_file(const char *file, char *args[])
{
    pid_t pid; /* Process ID for the child process. */
    int status; /* Variable to store the exit status of the child process. */

    /* Create a new process using fork. */
    pid = fork();
    if (pid == -1) /* Check if fork failed. */
    {
        perror("fork"); /* Print an error message if fork fails. */
        exit(EXIT_FAILURE); /* Exit the program on critical failure. */
    }

    if (pid == 0) /* Child process block. */
    {
        /* Execute the copied file with the provided arguments. */
        execve(file, args, environ);
        perror("execve failed"); /* Print an error message if execve fails. */
        exit(EXIT_FAILURE); /* Exit the child process on failure. */
    }

    /* Parent process block: wait for the child process to complete execution. */
    waitpid(pid, &status, 0);
}

