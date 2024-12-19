#include "main.h"
/**
 * path - function for the path
 * Return: 0 if it succeed
 */
int path(void)
{
	const char *path = oenv("PATH"); /*Retrieve the "PATH" environment variable*/

	if (path != NULL) /*Check if the environment variable exists*/
	{
		char *full_path = malloc(strlen(path) + strlen("/usr/bin") + 1);
		/*Construct the desired path*/

		strcpy(full_path, path);
		strcat(full_path, "/usr/bin");

		printf("Full path: %s\n", full_path); /*Print the constructed path*/

		free(full_path);
	}
	else
	{
		printf("Environment variable 'PATH' not found.\n");
	}
	return (0);
}
