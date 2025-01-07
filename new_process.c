#include "main.h"
/**
 * get_env - Function to get the env variable
 * @name: name of the var
 * Return: NULL
 */
char *get_env(const char *name)
{
	char **env; /* */
	char *entry;
	size_t len;

	len = strlen(name);
	for (env = environ; *env != NULL; env++)
	{
		entry = *env;
		if (strncmp(entry, name, len) == 0 && entry[len] == '=')
		{
			return (entry + len + 1);
		}
	}
	return (NULL);
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

	path = get_env("PATH");
	if (path != NULL)
	{
		path_copy = strdup(path);
		if (path_copy == NULL)
		{
		perror("shell");
			exit(EXIT_FAILURE);
		}
		dir = strtok(path_copy, ":");
		while (dir != NULL)
		{
			strcpy(full_path, dir);
			strcat(full_path, "/");
			strcat(full_path, args[0]);
			execve(full_path, args, environ);
			dir = strtok(NULL, ":");
		}
	}
		free(path_copy);
		return (-1);
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

	pid = fork();
	if (pid == 0)
	{
		if (try_exec(args) == -1)
		{
			perror("shell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("shell");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
return (1);
}

