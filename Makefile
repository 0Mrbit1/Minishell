NAME = minishell

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra 

# Source directories
PARSING_DIR = parsing
EXECUTION_DIR = execution
LIBFT_DIR = Libft

# Source files
PARSING_SRCS = src/$(PARSING_DIR)/parser.c \
               src/$(PARSING_DIR)/redirection.c \
               src/$(PARSING_DIR)/free_parsed_command.c \
			   src/$(PARSING_DIR)/tokenizer.c

EXECUTION_SRCS = src/$(EXECUTION_DIR)/builtins.c \
                 src/$(EXECUTION_DIR)/get_command_path.c \
                 src/$(EXECUTION_DIR)/output_error_exit.c \
                 src/$(EXECUTION_DIR)/dup_fd.c \
                 src/$(EXECUTION_DIR)/input_redirection.c \
                 src/$(EXECUTION_DIR)/output_redirection_append_mode.c \
                 src/$(EXECUTION_DIR)/execute_command.c \
                 src/$(EXECUTION_DIR)/input_redirection_herdoc.c \
                 src/$(EXECUTION_DIR)/output_redirection.c \
                 src/$(EXECUTION_DIR)/expand.c 

LIBFT_SRCS = src/$(LIBFT_DIR)/ft_atoi.c \
             src/$(LIBFT_DIR)/ft_isalpha.c \
             src/$(LIBFT_DIR)/ft_itoa.c \
             src/$(LIBFT_DIR)/ft_lstdelone_bonus.c \
             src/$(LIBFT_DIR)/ft_lstnew_bonus.c \
             src/$(LIBFT_DIR)/ft_memcpy.c \
             src/$(LIBFT_DIR)/ft_putendl_fd.c \
             src/$(LIBFT_DIR)/ft_strchr.c \
             src/$(LIBFT_DIR)/ft_strlcat.c \
             src/$(LIBFT_DIR)/ft_strncmp.c \
             src/$(LIBFT_DIR)/ft_substr.c \
             src/$(LIBFT_DIR)/ft_bzero.c \
             src/$(LIBFT_DIR)/ft_isascii.c \
             src/$(LIBFT_DIR)/ft_lstadd_back_bonus.c \
             src/$(LIBFT_DIR)/ft_lstiter_bonus.c \
             src/$(LIBFT_DIR)/ft_lstsize_bonus.c \
             src/$(LIBFT_DIR)/ft_memmove.c \
             src/$(LIBFT_DIR)/ft_putnbr_fd.c \
             src/$(LIBFT_DIR)/ft_strdup.c \
             src/$(LIBFT_DIR)/ft_strlcpy.c \
             src/$(LIBFT_DIR)/ft_strnstr.c \
             src/$(LIBFT_DIR)/ft_tolower.c \
             src/$(LIBFT_DIR)/ft_calloc.c \
             src/$(LIBFT_DIR)/ft_isdigit.c \
             src/$(LIBFT_DIR)/ft_lstadd_front_bonus.c \
             src/$(LIBFT_DIR)/ft_lstlast_bonus.c \
             src/$(LIBFT_DIR)/ft_memchr.c \
             src/$(LIBFT_DIR)/ft_memset.c \
             src/$(LIBFT_DIR)/ft_putstr_fd.c \
             src/$(LIBFT_DIR)/ft_striteri.c \
             src/$(LIBFT_DIR)/ft_strlen.c \
             src/$(LIBFT_DIR)/ft_strrchr.c \
             src/$(LIBFT_DIR)/ft_toupper.c \
             src/$(LIBFT_DIR)/ft_isalnum.c \
             src/$(LIBFT_DIR)/ft_isprint.c \
             src/$(LIBFT_DIR)/ft_lstclear_bonus.c \
             src/$(LIBFT_DIR)/ft_lstmap_bonus.c \
             src/$(LIBFT_DIR)/ft_memcmp.c \
             src/$(LIBFT_DIR)/ft_putchar_fd.c \
             src/$(LIBFT_DIR)/ft_split.c \
             src/$(LIBFT_DIR)/ft_strjoin.c \
             src/$(LIBFT_DIR)/ft_strmapi.c \
             src/$(LIBFT_DIR)/ft_strtrim.c \
             src/$(LIBFT_DIR)/get_next_line.c \
             src/$(LIBFT_DIR)/ft_free_split.c

# Object files
PARSING_OBJS = $(PARSING_SRCS:.c=.o)
EXECUTION_OBJS = $(EXECUTION_SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

# Libraries
LIBFT_LIB = libft.a
PARSING_LIB = libparsing.a
EXECUTION_LIB = libexecution.a
READLINE_LIB = -lreadline

# Compile all
all: $(NAME)

# Build minishell
$(NAME): $(LIBFT_LIB) $(PARSING_LIB) $(EXECUTION_LIB) $(READLINE_LIB)
	$(CC) $(CFLAGS) src/$(EXECUTION_DIR)/main.c -o $(NAME) -lreadline -L. -lexecution -lparsing -lft 

# Compile parsing library
$(PARSING_LIB): $(PARSING_OBJS)
	ar rcs $(PARSING_LIB) $(PARSING_OBJS)

# Compile execution library
$(EXECUTION_LIB): $(EXECUTION_OBJS)
	ar rcs $(EXECUTION_LIB) $(EXECUTION_OBJS)

# Compile libft library
$(LIBFT_LIB): $(LIBFT_OBJS)
	ar rcs $(LIBFT_LIB) $(LIBFT_OBJS)

# Clean object files
clean:
	rm -f $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS) 

# Clean object files and libraries
fclean: clean
	rm -f $(NAME) $(PARSING_LIB) $(EXECUTION_LIB) $(LIBFT_LIB)

# Rebuild everything
re: fclean all










