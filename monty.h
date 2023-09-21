#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct OpcodeHandler - Structure for opcode handlers
 * @opcode: The opcode
 * @handler: The function to handle the opcode
 *
 * Description: This structure holds information about opcode and its handler.
 */
typedef struct
{
	const char *opcode;
	void (*handler)(stack_t **stack, unsigned int line_number, char *arg);
} OpcodeHandler;

extern OpcodeHandler handlers[];
extern int num_handlers;


void push(stack_t **stack, int value);
void pall(stack_t **stack, unsigned int line_number);
void handle_push(stack_t **stack, unsigned int line_number, char *arg);
void handle_pall(stack_t **stack, unsigned int line_number, char *arg __attribute__((unused)));
int is_valid_integer(const char *str);
int main(int argc, char *argv[]);
int tokenize(char *line, char **opcode, char **arg);
void print_push_error(unsigned int line_number);
void print_unknown_instruction(unsigned int line_number, char *opcode);
void free_stack(stack_t **stack);
void handle_pint(stack_t **stack, unsigned int line_number, char *arg __attribute__((unused)));
int initialize(int argc, char *argv[], FILE **file, char **line, size_t *len, stack_t **stack, OpcodeHandler **handlers, int *num_handlers);
int process_file(FILE *file, stack_t **stack, OpcodeHandler *handlers, int num_handlers);
int cleanup(FILE *file, char *line, stack_t *stack);
int execute_instruction(char *line, unsigned int line_number, stack_t **stack,
                        OpcodeHandler *handlers, int num_handlers);
void cleanup_handlers(OpcodeHandler *handlers);

#endif
