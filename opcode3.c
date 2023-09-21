#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * handle_mod - Handles the 'mod' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_mod(stack_t **stack, unsigned int line_number,
		char *arg __attribute__((unused)))
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n",
			line_number);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n %= (*stack)->n;

	temp = *stack;
	*stack = (*stack)->next;
	free(temp);
}

/**
 * handle_pchar - Handles the 'pchar' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_pchar(stack_t **stack, unsigned int line_number,
		char *arg __attribute__((unused)))
{
	stack_t *temp;
	int ascii_value;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	ascii_value = (*stack)->n;

	if (ascii_value < 0 || ascii_value > 127)
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n",
			line_number);
		exit(EXIT_FAILURE);
	}
	putchar((char)ascii_value);
	putchar('\n');

	temp = *stack;
	*stack = (*stack)->next;
	free(temp);
}

/**
 * handle_pstr - Handles the 'pstr' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file.
 * @arg: unused attribute
 *
 * Return: none
 */
void handle_pstr(stack_t **stack, unsigned int line_number,
		char *arg __attribute__((unused)))
{
	stack_t *current = *stack;
	char *str = malloc(sizeof(char));
	char *temp_str = NULL;
	size_t str_len = 0;
	int ascii_value;
	(void)line_number;

	if (*stack == NULL)
	{
		putchar('\n');
		return;
	}
	if (str == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	while (current != NULL && (ascii_value = current->n) > 0
	       && ascii_value <= 127)
	{
		temp_str = malloc(str_len + 2);

		if (temp_str == NULL)
		{
			fprintf(stderr, "Error: malloc failed\n");
			free(str);
			exit(EXIT_FAILURE);
		}
		memcpy(temp_str, str, str_len);

		temp_str[str_len++] = (char)ascii_value;
		temp_str[str_len] = '\0';

		free(str);

		str = temp_str;
		current = current->next;
	}
	printf("%s\n", str);
	free(str);
}
/**
 * handle_rotl - Handles the 'rotl' opcode.
 * @stack: Pointer to the top of the stack.
 * @line_number: Current line number in the bytecode file (unused).
 * @arg: unused attribute
 *
 * Return: None
 */
void handle_rotl(stack_t **stack, unsigned int line_number,
		char *arg __attribute__((unused)))
{
	stack_t *current;
	stack_t *new_top;
	(void)line_number;

	if (*stack == NULL || (*stack)->next == NULL)
		return;

	current = *stack;
	new_top = current->next;

	while (current->next != NULL)
	{
		current = current->next;
	}
	    current->next = *stack;
	    (*stack)->prev = current;
	    (*stack)->next = NULL;
	    *stack = new_top;
	    (*stack)->prev = NULL;
}
