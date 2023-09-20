#include "monty.h"

/**
 * free_stack - Frees a stack (doubly linked list)
 * @stack: Pointer to a pointer to the top of the stack
 * should point to the top of the stack initially. After calling this function,
 * will be set to NULL, indicating an empty stack.
 * Return: nothing
 */

void free_stack(stack_t **stack)
{
	stack_t *current = *stack;
	stack_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*stack = NULL;
}
