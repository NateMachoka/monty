#include "monty.h"

/**
 * handle_add - Handles the 'add' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_add(stack_t **stack, unsigned int line_number,
		char *arg __attribute__((unused)))
{
	stack_t *top;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n",
			line_number);
		exit(EXIT_FAILURE);
	}

	top = *stack;

	*stack = (*stack)->next;
	(*stack)->n += top->n;

	free(top);
}

/**
 * handle_nop - Handles the 'nop' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_nop(stack_t **stack, unsigned int line_number,
		char *arg __attribute__((unused)))
{
	(void)stack;
	(void)line_number;
	(void)arg;
}
