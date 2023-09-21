#define _GNU_SOURCE
#include "monty.h"
#include <stdio.h>

/**
 * main - Entry point of monty application
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * Return: 0 for success, 1 otherwise
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	stack_t *stack = NULL;
	OpcodeHandler *handlers = NULL;
	int num_handlers = 0;

	if (initialize(argc, argv, &file, &line, &len, &stack, &handlers,
		       &num_handlers) != EXIT_SUCCESS)
	{
		return (EXIT_FAILURE);
	}
	if (process_file(file, &stack, handlers, num_handlers) != EXIT_SUCCESS)
	{
		cleanup(file, line, stack);
		cleanup_handlers(handlers);
		return (EXIT_FAILURE);
	}
	cleanup_handlers(handlers);
	return (cleanup(file, line, stack));
}

/**
 * initialize - Initialize the Monty interpreter.
 * @argv: Array of command-line arguments.
 * @argc: number of command-line arguments
 * @file: Pointer to the file to be opened.
 * @line: Pointer to the line buffer for reading file lines.
 * @len: Pointer to the length of the line buffer.
 * @stack: Pointer to the stack data structure.
 * @handlers: Pointer to the array of opcode handlers.
 * @num_handlers: Pointer to the number of opcode handlers.
 *
 * Return: 0 for success, 1 otherwise.
 */
int initialize(int argc, char *argv[], FILE **file, char **line, size_t *len,
	       stack_t **stack, OpcodeHandler **handlers, int *num_handlers)
{
	char *filename;
	OpcodeHandler temp_handlers[] = {
		{ "push", handle_push },
		{ "pall", handle_pall },
		{ "pint", handle_pint },
		{ "pop", handle_pop },
		{ NULL, NULL }
	};

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	filename = argv[1];
	*file = fopen(filename, "r");

	if (*file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		return (EXIT_FAILURE);
	}
	*num_handlers = sizeof(temp_handlers) / sizeof(temp_handlers[0]);

	*handlers = malloc(sizeof(OpcodeHandler) * (*num_handlers));
	if (*handlers == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		fclose(*file);
		return (EXIT_FAILURE);
	}
	memcpy(*handlers, temp_handlers, sizeof(temp_handlers));

	*line = NULL;
	*len = 0;
	*stack = NULL;

	return (EXIT_SUCCESS);
}

/**
 * execute_instruction - Executes a single Monty instruction.
 * @line: The input line containing the Monty instruction.
 * @line_number: Current line number in the bytecode file.
 * @stack: Pointer to the top of the stack.
 * @handlers: Array of opcode handlers.
 * @num_handlers: Number of opcode handlers.
 *
 * Return: 0 on success, 1 on failure.
 */
int execute_instruction(char *line, unsigned int line_number, stack_t **stack,
			OpcodeHandler *handlers, int num_handlers)
{
	char *opcode, *arg;
	int found, i;

	if (!tokenize(line, &opcode, &arg))
	{
		return (0);
	}
	found = 0;

	for (i = 0; i < num_handlers; i++)
	{
		if (strcmp(opcode, handlers[i].opcode) == 0)
		{
			handlers[i].handler(stack, line_number, arg);
			found = 1;
			break;
		}
	}
	if (!found)
	{
		print_unknown_instruction(line_number, opcode);
		return (1);
	}
	return (0);
}

/**
 * process_file - Process the Monty bytecode file.
 * @file: Pointer to the opened Monty bytecode file.
 * @stack: Pointer to the stack data structure.
 * @handlers: Array of opcode handlers.
 * @num_handlers: Number of opcode handlers.
 *
 * Return: 0 for success, 1 otherwise.
 */
int process_file(FILE *file, stack_t **stack, OpcodeHandler *handlers,
		 int num_handlers)
{
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 0;

	while (getline(&line, &len, file) != -1)
	{
		line_number++;

		if (execute_instruction(line, line_number, stack,
					handlers, num_handlers))
		{
			free(line);
			return (EXIT_FAILURE);
		}
	}
	free(line);
	return (EXIT_SUCCESS);
}

/**
 * cleanup - Clean up resources used by the Monty interpreter.
 * @file: Pointer to the opened Monty bytecode file.
 * @line: Pointer to the line buffer for reading file lines.
 * @stack: Pointer to the stack data structure.
 *
 * Return: 0 for success.
 */
int cleanup(FILE *file, char *line, stack_t *stack)
{
	fclose(file);
	free(line);
	free_stack(&stack);

	return (EXIT_SUCCESS);
}
