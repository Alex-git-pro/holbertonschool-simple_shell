#include "main.h"
/**
 * main - main function
 * Return: 0 on success
 */

int main(void)
{
	if (isatty(STDIN_FILENO) == 1) /*Check if STDIN is connected to a terminal*/
	{
		shell_interactive(); /*Launch the interactive mode*/
	}
	else
	{
		shell_no_interactive(); /*Launch the no-interactive mode*/
	}
	return (0);
}
