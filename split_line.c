#include "main.h"
/**
 * split_line - Split a string into multiple strings
 * @line: line to be splitted
 *
 * Return: pointer to the new array
 */
char **split_line(char *line)
{
	int bufsize = 64; /*Initial size of the buffer to stock tokens*/
	int i = 0; /*Token position*/
	char **tokens = malloc(bufsize * sizeof(char *)); /*Dynamic array*/
	char *token; /*Pointer to stock each token individually*/

	if (!tokens) /*If malloc fails, print an error & exit*/
	{
		fprintf(stderr, "allocation error in split_line: tokens\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIM);
	{
		while (token != NULL) /*Handle comments*/
		if (token[0] == '#')
		{
			break;
		}
		tokens[i] = token; /*Stock the token*/
		i++;
		if (i >= bufsize) /*If the array is full, double its size*/
		{
			bufsize += bufsize;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens) /*If realloc fails, print an error & exit*/
			{
				fprintf(stderr, "reallocation error on split_line: tokens");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM); /*Tokenization continue on the same line*/
	}
	tokens[i] = NULL; /*Add NULL at the end of the array*/
	return (tokens); /*Returns the array with the tokens*/
}
