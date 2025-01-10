#include "shell.h"
/**
 * main - main function
 * Return: Nothing
 */
int main(void)
{
	char *input = NULL; /* Pointer for user input */
	size_t input_size = 0; /* Size of the input buffer */
	ssize_t chars_read; /* Number of characters read from stdin */

	/* Check if input is from a terminal */
	if (isatty(STDIN_FILENO))
	{
		printf("$ "); /* Display the shell prompt */
	}

	while (1)
	{
		chars_read = getline(&input, &input_size, stdin); /* Read user input */

		if (chars_read == -1)
		{
			/* If Ctrl + C is pressed, reset the shell without quitting */
			if (isatty(STDIN_FILENO))
			{
				printf("\n$ "); /* Display the prompt again */
			}
			clearerr(stdin); /* Clear the input buffer to avoid infinite loops */
			continue; /* Restart the loop without exiting */
		}

		input[strcspn(input, "\n")] = 0; /* Remove newline character from input */

		if (strlen(input) > 0)
			execute_command(input); /* Execute the command entered by the user */

		/* Display the prompt again only if the input is interactive */
		if (isatty(STDIN_FILENO))
		{
			printf("$ "); /* Display the shell prompt */
		}
	}

	free(input); /* Free the allocated memory for input */
	return (0); /* Return 0 to indicate success */
}
