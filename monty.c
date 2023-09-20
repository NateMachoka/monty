#define _GNU_SOURCE
#include "monty.h"
#include <stdio.h>

/**
 * main - Entry point of monty application
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Return: 0 for success, 1 otherwise.
 */
int main(int argc, char *argv[])
{
	char *filename;
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 0;
	stack_t *stack = NULL;
	char *opcode, *arg;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	filename = argv[1];

	file = fopen(filename, "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		return EXIT_FAILURE;
	}
	while (getline(&line, &len, file) != -1)
	{
		line_number++;

		if (tokenize(line, &opcode, &arg))
		{
			if (strcmp(opcode, "push") == 0)
			{
				handle_push(&stack, line_number, arg);
			}
			else if (strcmp(opcode, "pall") == 0)
			{
				handle_pall(&stack, line_number);
			}
			else
			{
				print_unknown_instruction(line_number, opcode);
			}
		}
	}
	free(line);
	fclose(file);
	free_stack(&stack);

	return (0);
}
