SRCS = shell.c parser.c helper_function.c tokenizer.c redirection.c free_parsed_command.c ft_split.c executor.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

minishell: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o minishell -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f minishell

re: fclean minishell
 
