#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

/**
 * print_push_error - Prints an error message for a 'push' opcode error.
 * @line_number: The line number where the error occurred.
 *
 * Return: exits the program with a failure status.
 */
void print_push_error(unsigned int line_number)
{
	fprintf(stderr, "L%u: usage: push integer\n", line_number);
	exit(EXIT_FAILURE);
}

/**
 * print_unknown_instruction - Prints an error message for an unknown opcode.
 * @line_number: The line number where the error occurred.
 * @opcode: The unknown opcode.
 *
 * Return: exits the program with a failure status.
 */
void print_unknown_instruction(unsigned int line_number, char *opcode)
{
	fprintf(stderr, "L%u: unknown instruction %s", line_number, opcode);
	exit(EXIT_FAILURE);
}
