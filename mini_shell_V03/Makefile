NAME = minishell

CC = gcc
CFLAGS = -Wall # -Wextra -Werror

SRCS = free_parsed_command.c \
       main.c \
       parser.c \
       builtins.c \
       ft_split.c \
       redirection.c \
       dup_fd.c \
       get_command_path.c \
       output_error_exit.c \
       tokenizer.c \
       ft_strjoin.c \
       execute_command.c \
       input_redirection.c \
       output_redirection.c \
       input_redirection_herdoc.c \
       output_redirection_append_mode.c \
       helper_function.c \
       command_handler.c
       # tok.c \
       # expand.c \
 
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
