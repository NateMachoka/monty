#include "monty.h"

/**
 * handle_push - Handles the 'push' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: The argument following the 'push' opcode (should be an integer).
 *
 * Return: none
 */
void handle_push(stack_t **stack, unsigned int line_number, char *arg)
{
	int value;

	if (arg == NULL || !is_valid_integer(arg))
        {
                fprintf(stderr, "L%u: usage: push integer\n", line_number);
                exit(EXIT_FAILURE);
        }
        value = atoi(arg);
        push(stack, value);
}

/**
 * handle_pall - Handles the 'pall' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 *
 * This function prints all values on the stack.
 */
void handle_pall(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
		return;
	pall(stack, line_number);
}
