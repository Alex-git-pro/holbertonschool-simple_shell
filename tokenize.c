#include "main.h"

/**
 * tokenize_line - Tokenizes a command line string into an array of arguments.
 * @line: The input command string.
 * Return: An array of arguments.
 */
char **tokenize_line(char *line)
{
	char **args;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * 64);
	if (!args)
	{
		perror("malloc failed");
		exit(1);
	}

	token = strtok(line, " ");
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	return (args);
}
