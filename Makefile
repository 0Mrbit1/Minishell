# Variables
CC = gcc
CFLAGS = -Wall -Wextra
AR = ar
ARFLAGS = rcs
LIBDIR = lib
SRC_DIR = src
EXEC_DIR = $(SRC_DIR)/execution
PARSE_DIR = $(SRC_DIR)/parsing
TOKEN_DIR = $(SRC_DIR)/tokenization
LIBFT_DIR = $(SRC_DIR)/Libft

# Library files
EXEC_LIB = $(LIBDIR)/libexecution.a
PARSE_LIB = $(LIBDIR)/libparsing.a
TOKEN_LIB = $(LIBDIR)/libtokenization.a
LIBFT_LIB = $(LIBDIR)/libft.a

# Source files
EXEC_SRCS = \
    $(EXEC_DIR)/builtins.c \
    $(EXEC_DIR)/execute_command.c \
    $(EXEC_DIR)/get_command_path.c \
    $(EXEC_DIR)/input_redirection_herdoc.c \
    $(EXEC_DIR)/output_redirection_append_mode.c \
    $(EXEC_DIR)/piping.c \
    $(EXEC_DIR)/dup_fd.c \
    $(EXEC_DIR)/expand.c \
    $(EXEC_DIR)/input_redirection.c \
    $(EXEC_DIR)/output_error_exit.c \
    $(EXEC_DIR)/output_redirection.c

PARSE_SRCS = $(PARSE_DIR)/parser.c

TOKEN_SRCS = \
    $(TOKEN_DIR)/tokenizer.c \
    $(TOKEN_DIR)/type_checkers.c

LIBFT_SRCS = \
    $(LIBFT_DIR)/ft_isalpha.c $(LIBFT_DIR)/ft_isdigit.c $(LIBFT_DIR)/ft_isalnum.c \
    $(LIBFT_DIR)/ft_isascii.c $(LIBFT_DIR)/ft_isprint.c \
    $(LIBFT_DIR)/ft_strlen.c $(LIBFT_DIR)/ft_memset.c $(LIBFT_DIR)/ft_bzero.c \
    $(LIBFT_DIR)/ft_memcpy.c $(LIBFT_DIR)/ft_memmove.c $(LIBFT_DIR)/ft_strlcpy.c \
    $(LIBFT_DIR)/ft_strlcat.c $(LIBFT_DIR)/ft_toupper.c $(LIBFT_DIR)/ft_tolower.c \
    $(LIBFT_DIR)/ft_strchr.c $(LIBFT_DIR)/ft_strrchr.c $(LIBFT_DIR)/ft_strncmp.c \
    $(LIBFT_DIR)/ft_memchr.c $(LIBFT_DIR)/ft_memcmp.c $(LIBFT_DIR)/ft_strnstr.c \
    $(LIBFT_DIR)/ft_atoi.c $(LIBFT_DIR)/ft_calloc.c $(LIBFT_DIR)/ft_strdup.c \
    $(LIBFT_DIR)/ft_substr.c $(LIBFT_DIR)/ft_strjoin.c $(LIBFT_DIR)/ft_strtrim.c \
    $(LIBFT_DIR)/ft_split.c $(LIBFT_DIR)/ft_itoa.c $(LIBFT_DIR)/ft_strmapi.c \
    $(LIBFT_DIR)/ft_striteri.c $(LIBFT_DIR)/ft_putchar_fd.c $(LIBFT_DIR)/ft_putstr_fd.c \
    $(LIBFT_DIR)/ft_putendl_fd.c $(LIBFT_DIR)/ft_putnbr_fd.c $(LIBFT_DIR)/get_next_line.c

# Object files
EXEC_OBJS = $(EXEC_SRCS:$(EXEC_DIR)/%.c=$(LIBDIR)/%.o)
PARSE_OBJS = $(PARSE_SRCS:$(PARSE_DIR)/%.c=$(LIBDIR)/%.o)
TOKEN_OBJS = $(TOKEN_SRCS:$(TOKEN_DIR)/%.c=$(LIBDIR)/%.o)
LIBFT_OBJS = $(LIBFT_SRCS:$(LIBFT_DIR)/%.c=$(LIBDIR)/libft_%.o)

# Default target
all: $(LIBFT_LIB) $(EXEC_LIB) $(PARSE_LIB) $(TOKEN_LIB)

# Rule to create the libft library
$(LIBFT_LIB): $(LIBFT_OBJS)
	@mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $(LIBFT_OBJS)

# Rule to create the execution library
$(EXEC_LIB): $(EXEC_OBJS) $(LIBFT_LIB)
	@mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $(EXEC_OBJS)

# Rule to create the parsing library
$(PARSE_LIB): $(PARSE_OBJS) $(LIBFT_LIB)
	@mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $(PARSE_OBJS)

# Rule to create the tokenization library
$(TOKEN_LIB): $(TOKEN_OBJS) $(LIBFT_LIB)
	@mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $(TOKEN_OBJS)

# Rule to compile libft objects
$(LIBDIR)/libft_%.o: $(LIBFT_DIR)/%.c
	@mkdir -p $(LIBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile execution objects
$(LIBDIR)/%.o: $(EXEC_DIR)/%.c
	@mkdir -p $(LIBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile parsing objects
$(LIBDIR)/%.o: $(PARSE_DIR)/%.c
	@mkdir -p $(LIBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile tokenization objects
$(LIBDIR)/%.o: $(TOKEN_DIR)/%.c
	@mkdir -p $(LIBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(LIBDIR)/*.o
fclean:
	rm -f $(LIBDIR)/*.a

# Phony targets
.PHONY: all clean

