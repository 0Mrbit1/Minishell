NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = shell.c \
       parser.c \
       redirection.c \
       free_parsed_command.c \
       ft_split.c \
       tokenizer.c

OBJS = $(SRCS:.c=.o)

LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

