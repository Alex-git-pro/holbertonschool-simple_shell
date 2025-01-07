#include "main.h"
/**
 * get_env - Function to get the env variable
 * @name: name of the var
 * Return: NULL if not found, pointer to value if found
 */
char *get_env(const char *name)
{
	char **env; /*Pointer to iterate though env variables*/
	char *entry;/*Pointer to hold each env var entry*/
	size_t len;/*Length of the var name*/

	len = strlen(name);
	for (env = environ; *env != NULL; env++)/*Iterate through all env var*/
	{
		entry = *env;
		if (strncmp(entry, name, len) == 0 && entry[len] == '=')
		/*Check if current entry matches the requested name*/
		{
			return (entry + len + 1);
			/*Return pointer to the value part of the environment variable*/
		}
	}
	return (NULL); /*Return NULL if the variable is not found*/
}
/**
 * try_exec - Function to attempt to exec a command in each PATH dir
 * @args: Array of string containing the prog name and args
 * Return: -1 if failure, nothing otherwise
 */
int try_exec(char **args)
{
	char *path;
	char *path_copy;
	char *dir;
	char full_path[1024];

	path = get_env("PATH");/*Retrieve the PATH env variable*/
	if (path != NULL)
	{
		path_copy = strdup(path);
		if (path_copy == NULL)
		{
		perror("shell");
			exit(EXIT_FAILURE);
		}
		/*Tokenize the PATH string into individuals directories*/
		dir = strtok(path_copy, ":");
		while (dir != NULL)
		{
			/*Construct the full path of the command*/
			strcpy(full_path, dir);
			strcat(full_path, "/");
			strcat(full_path, args[0]);
			execve(full_path, args, environ);/*Attempt to execute the command*/
			/*If execve succeeds, doesn't return. If it return if failed*/
			dir = strtok(NULL, ":");/*Move to the next directory PATH*/
		}
	}
		free(path_copy);/*Free the memory allocated for the PATH copy*/
		return (-1);/*If we reach here, command was not found in any PATH dir*/
}
/**
 * new_process - Function to create a new process
 * @args: args
 * Return: 1
 */
int new_process(char **args)
{
	pid_t pid;
	int status;

	pid = fork();/*Fork a nex process*/
	if (pid == 0)
	{
		/*Child process*/
		if (try_exec(args) == -1)
		{
			/*If execution fails, print error and exit*/
			perror("shell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{	/*Fork failed*/
		perror("shell");
	}
	else
	{	/*Parent process*/
		do {
			waitpid(pid, &status, WUNTRACED);
			/*Wait for the child process to change state*/
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
return (1);
}
