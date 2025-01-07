#include "main.h"
/**
 * path - function for the path
 * Return: 0 if it succeed
 */
int path(void)
{
	char *args[] = {"PATH", NULL}; /*Argument array for oenv() function*/
	int result = oenv(args); /*Call oenv() to check PATH env var*/
	char *full_path;

	if (result == 0) /*If PATH exists*/
	{
		char *path_value = getenv("PATH"); /*Retrieve current PATH value*/

		if (path_value != NULL)
		{
			full_path = malloc(strlen(path_value) + strlen(":/usr/bin") + 1);

			if (full_path == NULL) /*Error handling for memory allocation*/
			{
				perror("malloc failed");
				return (1);
			}

			strcpy(full_path, path_value); /*Concat original PATH*/
			strcat(full_path, ":/usr/bin");

			printf("Full path: %s\n", full_path); /*Display the modified path*/

			free(full_path);
		}
		else
		{
			printf("Failed to get PATH value.\n");
		}
	}
	else
	{
		printf("Environment variable 'PATH' not found.\n");
	}
	return (0);
}
