#include "main.h"

/**
 * exit_shell - Handles the exit command.
 * @args: The command arguments.
 * Return: None.
 */
void exit_shell(char **args)
{
	/* Exit the shell with the given status or 0 by default */
	int status = 0;

	if (args[1]) /* If there is an argument after exit */
	{
		status = atoi(args[1]);
	}

	write(STDOUT_FILENO, "Exiting shell...\n", 17);
	exit(status);
}

/**
 * cd_builtin - Handles the built-in "cd" command.
 * @args: The command arguments.
 * Return: None.
 */
void cd_builtin(char **args)
{
	if (!args[1] || _strcmp(args[1], "~") == 0) /* Go to home directory */
	{
		if (chdir(getenv("HOME")) != 0)
			perror("cd");
	}
	else if (chdir(args[1]) != 0) /* Change to the specified directory */
	{
		perror("cd");
	}
}

/**
 * _strcmp - Compares two strings.
 * @s1: First string.
 * @s2: Second string.
 * Return: 0 if equal, non-zero otherwise.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * ls_builtin - Implements the "ls" command for the shell.
 * @args: Arguments for the ls command (e.g., directory to list).
 * Return: 0 on success, -1 on failure.
 */
int ls_builtin(char **args)
{
	DIR *dir;
	struct dirent *entry;
	char *dir_name = ".";

	if (args[1])
	{
		dir_name = args[1];
	}

	dir = opendir(dir_name);
	if (!dir)
	{
		return (-1);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}
	closedir(dir);

	return (0);
}
