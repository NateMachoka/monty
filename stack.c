#include "monty.h"

/**
 * push - Pushes an element onto the stack.
 * @stack: Pointer to a pointer to the top of the stack.
 * @value: The integer value to be pushed onto the stack.
 *
 * Return: No return value.
 */
void push(stack_t **stack, int value)
{
	stack_t *new_node = malloc(sizeof(stack_t));

	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack)
		(*stack)->prev = new_node;

	*stack = new_node;
}

/**
 * pall - Prints all values on the stack.
 * @stack: Pointer to a pointer to the top of the stack.
 * @line_number: The current line number in the bytecode file (unused).
 *
 *
 * Return: No return value.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)line_number;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
