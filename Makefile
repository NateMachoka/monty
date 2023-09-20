CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c89
OBJS = monty.o stack.o opcode.o tokenizer.o handle_error.o memory.o

monty: $(OBJS)
	$(CC) $(CFLAGS) -o monty $(OBJS)

%.o: %.c monty.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f monty $(OBJS)
