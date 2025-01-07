#include "main.h"
/**
 * split_line - Split a string into multiple strings
 * @line: line to be splitted
 *
 * Return: pointer to the new array
 */
char **split_line(char *line)
{
	int bufsize = TOK_BUFF_SIZE; /*Initial size of the buffer to stock tokens*/
	int pos = 0; /*Token position counter*/
	char **tokens = malloc(bufsize * sizeof(char *)); /*Dynamic array*/
	char *token; /*Pointer to stock each token individually*/

	if (!tokens) /*Check if mem alloc was successful*/
	{
		fprintf(stderr, "shell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIM); /*Get the first token*/
	while (token != NULL) /*Loop through the string to extract all tokens*/
	{
		tokens[pos] = token; /*Store the token in the array*/
		pos++;
		if (pos >= bufsize)/*If buffer is full, resize it*/
		{
			bufsize += TOK_BUFF_SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			/*Realloc mem with new size*/
			if (!tokens) /*Check if realloc was successful*/
			{
				fprintf(stderr, "shell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);/*Get the next token*/
	}
	tokens[pos] = NULL;/*NULL terminate the array of tokens*/
	return (tokens); /*Return the array of tokens*/
}
