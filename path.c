#include "main.h"
/**
 * path - function for the path
 * Return: 0 if it succeed
 */
int path(void)
{
	char *args[] = {"PATH", NULL};
	int result = oenv(args);
	char *full_path;

	if (result == 0)
	{
		char *path_value = getenv("PATH");

		if (path_value != NULL)
		{
			full_path = malloc(strlen(path_value) + strlen(":/usr/bin") + 1);

			if (full_path == NULL)
			{
				perror("malloc failed");
				return (1);
			}

			strcpy(full_path, path_value);
			strcat(full_path, ":/usr/bin");

			printf("Full path: %s\n", full_path);

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
