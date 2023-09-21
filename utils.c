#include "monty.h"

/**
* is_valid_integer - Checks if a string is a number
* @str: The string
*
* Return: 1 if true, 0 otherwise
*/

int is_valid_integer(const char *str)
{
	int i = 0;

	if (str == NULL || *str == '\0')
	{
		return (0);
	}
	if (str[0] == '-' || str[0] == '+')
	{
		i = 1;
	}
	for (; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
	}
	return (1);
}

/**
 * initialize_handlers - a function that initializes temp_handlers
 * @handlers: Pointer to the array of opcode handlers
 * @num_handlers: Pointer to the number of opcode handlers
 *
 * Return: none
 */
void initialize_handlers(OpcodeHandler **handlers, int *num_handlers)
{
	OpcodeHandler temp_handlers[] = {
		{ "push", handle_push },
		{ "pall", handle_pall },
		{ "pint", handle_pint },
		{ "pop", handle_pop },
		{ "swap", handle_swap },
		{ "add", handle_add },
		{ "sub", handle_sub },
		{ "div", handle_div },
		{ "mod", handle_mod },
		{ "nop", handle_nop },
		{ "pchar", handle_pchar },
		{ "mul", handle_mul },
		{ NULL, NULL }
	};

	*num_handlers = sizeof(temp_handlers) / sizeof(temp_handlers[0]);

	*handlers = malloc(sizeof(OpcodeHandler) * (*num_handlers));
	if (*handlers == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	memcpy(*handlers, temp_handlers, sizeof(temp_handlers));
}
