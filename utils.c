#include "shell.h"

/**
* get_location - Retrieves the full path of a given command from PATH variable
* @command: Command name whose location needs to be found
*
* Return: Full path of the command or NULL if not found
*
*/
char *get_location(char *command)
{
	char **env;
	char *path = NULL;
	char *path_copy;
	char *path_token;
	struct stat buffer;

	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path = (*env + 5); /* Skip "PATH="*/
			break;
		}
	}

	if (!path) /*if PATH is not set*/
		return (NULL);

	path_copy = strdup(path); /*Duplicate PATH string for tokenization*/
	path_token = strtok(path_copy, ":"); /*Tokenize based on ':'*/

	while (path_token != NULL) /*Iterate through each directory in PATH*/
	{
		char file_path[MAX_INPUT_SIZE]; /*Buffer for full file path*/

		sprintf(file_path, "%s/%s", path_token, command); /*Construct full path*/

		if (stat(file_path, &buffer) == 0) /*Check if file exists*/
		{
			free(path_copy); /*Free duplicated PATH string*/
			return (strdup(file_path)); /*Command found*/
		}

	   path_token = strtok(NULL, ":"); /*Move to next directory in PATH*/
	}

	free(path_copy); /* Free duplicated PATH string if not found*/
	return (NULL); /* Command not found in any directory in PATH*/
}
