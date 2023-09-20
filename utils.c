#include "monty.h"

/**
* is_number - Checks if a string is a number
* @str: The string
*
* Return: 1 if true, 0 otherwise
*/

int is_valid_integer(const char *str)
{
	int i;

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
