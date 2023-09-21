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

	if (arg == NULL)
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
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_pall(stack_t **stack, unsigned int line_number,
		 char *arg __attribute__((unused)))
{
	if (*stack == NULL)
		return;
	pall(stack, line_number);
}
/**
 * handle_pint - Handles the 'pint' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_pint(stack_t **stack, unsigned int line_number,
		 char *arg __attribute__((unused)))
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * handle_pop - Handles the 'pop' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_pop(stack_t **stack, unsigned int line_number,
		char *arg __attribute__((unused)))
{
	stack_t *top;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	top = *stack;

	if (top->next != NULL)
	{
		*stack = top->next;
		(*stack)->prev = NULL;
	}
	else
	{
		*stack = NULL;
	}

	free(top);
}

/**
 * handle_swap - Handles the 'swap' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_swap(stack_t **stack, unsigned int line_number,
		 char *arg __attribute__((unused)))
{
	int tmp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n",
			line_number);
		exit(EXIT_FAILURE);
	}
	tmp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = tmp;
}
