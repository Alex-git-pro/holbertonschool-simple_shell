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

	while (1)
	{
		display_prompt(); /* Display the shell prompt */
		chars_read = getline(&input, &input_size, stdin); /* Read user input */

		if (chars_read == -1)
		{
			printf("\n"); /* Handle end of input */
			break;
		}

		input[strcspn(input, "\n")] = 0; /* Remove newline character */

		if (strlen(input) > 0)
			execute_command(input); /* Execute the command entered by the user */
	}

	free(input); /* Free allocated memory for input */
	return (0); /* Return success */
}

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
	printf("$ "); /* Simple prompt */
}
