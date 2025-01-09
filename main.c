#include "shell.h"

/**
 * main - Entry point of the shell program.
 *
 * Return: Always 0 on success.
 */
int main(void)
{
	char *input = NULL; /* Pointer for user input */
	size_t input_size = 0; /* Size of the input buffer */
	ssize_t chars_read; /* Number of characters read */

	/* Check if the input is from a terminal */
	if (isatty(STDIN_FILENO))
	{
		printf("$ "); /* Display the shell prompt */
	}

	while (1)
	{
		chars_read = getline(&input, &input_size, stdin); /* Read user input */

		if (chars_read == -1)
		{
			break;
		}

		input[strcspn(input, "\n")] = 0; /* Remove newline character */

		if (strlen(input) > 0)
			execute_command(input); /* Execute the command entered by the user */

		/* Prompt again only if the input is interactive */
		if (isatty(STDIN_FILENO))
		{
			printf("$ "); /* Display the shell prompt again */
		}
	}

	free(input); /* Free allocated memory for input */
	return (0); /* Return success */
}
