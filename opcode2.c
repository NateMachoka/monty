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

/**
 * handle_sub - Handles the 'sub' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_sub(stack_t **stack, unsigned int line_number,
		char *arg __attribute__((unused)))
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n",
			line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n -= (*stack)->n;

	temp = *stack;
	*stack = (*stack)->next;
	free(temp);
}

#include <stdio.h>
#include <stdlib.h>

/**
 * handle_div - Handles the 'div' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_div(stack_t **stack, unsigned int line_number,
		char *arg __attribute__((unused)))
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't div, stack too short\n",
			line_number);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n /= (*stack)->n;

	temp = *stack;
	*stack = (*stack)->next;
	free(temp);
}

#include <stdio.h>
#include <stdlib.h>

/**
 * handle_mul - Handles the 'mul' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_mul(stack_t **stack, unsigned int line_number,
		char *arg __attribute__((unused)))
{
	stack_t *temp;
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n",
			line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n *= (*stack)->n;

	temp = *stack;
	*stack = (*stack)->next;
	free(temp);
}
