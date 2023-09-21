#include "monty.h"

/**
 * tokenize - tokenizes the input line of Monty code, splitting it into an
 * opcode and an argument. uses space, tab, and newline characters as delims
 * @line: The input line to tokenize.
 * @opcode: Pointer to store the extracted opcode.
 * @arg: Pointer to store the extracted argument.
 *
 *It uses space, tab, and newline characters as delimiters.
 *
 * Return: - 1 if a valid opcode, - 0 if no opcode is found (end of line)
 */
int tokenize(char *line, char **opcode, char **arg)
{
	*opcode = strtok(line, " \t\n");
	*arg = strtok(NULL, " \t\n");

	return (*opcode != NULL);
}
