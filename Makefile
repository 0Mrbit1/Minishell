# Variables
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
EXEC_OBJS = $(LIBDIR)/builtins.o $(LIBDIR)/execute_command.o $(LIBDIR)/get_command_path.o \
            $(LIBDIR)/input_redirection_herdoc.o $(LIBDIR)/output_redirection_append_mode.o \
            $(LIBDIR)/piping.o $(LIBDIR)/dup_fd.o $(LIBDIR)/expand.o \
            $(LIBDIR)/input_redirection.o $(LIBDIR)/output_error_exit.o \
            $(LIBDIR)/output_redirection.o

PARSE_OBJS = $(LIBDIR)/parser.o

TOKEN_OBJS = $(LIBDIR)/tokenizer.o $(LIBDIR)/type_checkers.o

LIBFT_OBJS = $(LIBDIR)/libft_ft_isalpha.o $(LIBDIR)/libft_ft_isdigit.o $(LIBDIR)/libft_ft_isalnum.o \
             $(LIBDIR)/libft_ft_isascii.o $(LIBDIR)/libft_ft_isprint.o \
             $(LIBDIR)/libft_ft_strlen.o $(LIBDIR)/libft_ft_memset.o $(LIBDIR)/libft_ft_bzero.o \
             $(LIBDIR)/libft_ft_memcpy.o $(LIBDIR)/libft_ft_memmove.o $(LIBDIR)/libft_ft_strlcpy.o \
             $(LIBDIR)/libft_ft_strlcat.o $(LIBDIR)/libft_ft_toupper.o $(LIBDIR)/libft_ft_tolower.o \
             $(LIBDIR)/libft_ft_strchr.o $(LIBDIR)/libft_ft_strrchr.o $(LIBDIR)/libft_ft_strncmp.o \
             $(LIBDIR)/libft_ft_memchr.o $(LIBDIR)/libft_ft_memcmp.o $(LIBDIR)/libft_ft_strnstr.o \
             $(LIBDIR)/libft_ft_atoi.o $(LIBDIR)/libft_ft_calloc.o $(LIBDIR)/libft_ft_strdup.o \
             $(LIBDIR)/libft_ft_substr.o $(LIBDIR)/libft_ft_strjoin.o $(LIBDIR)/libft_ft_strtrim.o \
             $(LIBDIR)/libft_ft_split.o $(LIBDIR)/libft_ft_itoa.o $(LIBDIR)/libft_ft_strmapi.o \
             $(LIBDIR)/libft_ft_striteri.o $(LIBDIR)/libft_ft_putchar_fd.o $(LIBDIR)/libft_ft_putstr_fd.o \
             $(LIBDIR)/libft_ft_putendl_fd.o $(LIBDIR)/libft_ft_putnbr_fd.o $(LIBDIR)/libft_get_next_line.o

# Default target
all: $(LIBFT_LIB) $(EXEC_LIB) $(PARSE_LIB) $(TOKEN_LIB)

# Rule to create the libft library
$(LIBFT_LIB): $(LIBFT_OBJS)
	$(AR) $(ARFLAGS) $@ $(LIBFT_OBJS)
	rm -f $(LIBFT_OBJS)

# Rule to create the execution library
$(EXEC_LIB): $(EXEC_OBJS) $(LIBFT_LIB)
	$(AR) $(ARFLAGS) $@ $(EXEC_OBJS)
	rm -f $(EXEC_OBJS)

# Rule to create the parsing library
$(PARSE_LIB): $(PARSE_OBJS) $(LIBFT_LIB)
	$(AR) $(ARFLAGS) $@ $(PARSE_OBJS)
	rm -f $(PARSE_OBJS)

# Rule to create the tokenization library
$(TOKEN_LIB): $(TOKEN_OBJS) $(LIBFT_LIB)
	$(AR) $(ARFLAGS) $@ $(TOKEN_OBJS)
	rm -f $(TOKEN_OBJS)

# Rule to compile libft objects
$(LIBDIR)/libft_ft_isalpha.o: $(LIBFT_DIR)/ft_isalpha.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_isdigit.o: $(LIBFT_DIR)/ft_isdigit.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_isalnum.o: $(LIBFT_DIR)/ft_isalnum.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_isascii.o: $(LIBFT_DIR)/ft_isascii.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_isprint.o: $(LIBFT_DIR)/ft_isprint.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_strlen.o: $(LIBFT_DIR)/ft_strlen.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_memset.o: $(LIBFT_DIR)/ft_memset.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_bzero.o: $(LIBFT_DIR)/ft_bzero.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_memcpy.o: $(LIBFT_DIR)/ft_memcpy.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_memmove.o: $(LIBFT_DIR)/ft_memmove.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_strlcpy.o: $(LIBFT_DIR)/ft_strlcpy.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_strlcat.o: $(LIBFT_DIR)/ft_strlcat.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_toupper.o: $(LIBFT_DIR)/ft_toupper.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_tolower.o: $(LIBFT_DIR)/ft_tolower.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_strchr.o: $(LIBFT_DIR)/ft_strchr.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_strrchr.o: $(LIBFT_DIR)/ft_strrchr.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_strncmp.o: $(LIBFT_DIR)/ft_strncmp.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_memchr.o: $(LIBFT_DIR)/ft_memchr.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_memcmp.o: $(LIBFT_DIR)/ft_memcmp.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_strnstr.o: $(LIBFT_DIR)/ft_strnstr.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_atoi.o: $(LIBFT_DIR)/ft_atoi.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_calloc.o: $(LIBFT_DIR)/ft_calloc.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_strdup.o: $(LIBFT_DIR)/ft_strdup.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_substr.o: $(LIBFT_DIR)/ft_substr.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_strjoin.o: $(LIBFT_DIR)/ft_strjoin.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_strtrim.o: $(LIBFT_DIR)/ft_strtrim.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_split.o: $(LIBFT_DIR)/ft_split.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_itoa.o: $(LIBFT_DIR)/ft_itoa.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_strmapi.o: $(LIBFT_DIR)/ft_strmapi.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_striteri.o: $(LIBFT_DIR)/ft_striteri.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_putchar_fd.o: $(LIBFT_DIR)/ft_putchar_fd.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_putstr_fd.o: $(LIBFT_DIR)/ft_putstr_fd.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_putendl_fd.o: $(LIBFT_DIR)/ft_putendl_fd.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_ft_putnbr_fd.o: $(LIBFT_DIR)/ft_putnbr_fd.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/libft_get_next_line.o: $(LIBFT_DIR)/get_next_line.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile execution objects
$(LIBDIR)/builtins.o: $(EXEC_DIR)/builtins.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/execute_command.o: $(EXEC_DIR)/execute_command.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/get_command_path.o: $(EXEC_DIR)/get_command_path.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/input_redirection_herdoc.o: $(EXEC_DIR)/input_redirection_herdoc.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/output_redirection_append_mode.o: $(EXEC_DIR)/output_redirection_append_mode.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/piping.o: $(EXEC_DIR)/piping.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/dup_fd.o: $(EXEC_DIR)/dup_fd.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/expand.o: $(EXEC_DIR)/expand.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/input_redirection.o: $(EXEC_DIR)/input_redirection.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/output_error_exit.o: $(EXEC_DIR)/output_error_exit.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/output_redirection.o: $(EXEC_DIR)/output_redirection.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile parsing objects
$(LIBDIR)/parser.o: $(PARSE_DIR)/parser.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile tokenization objects
$(LIBDIR)/tokenizer.o: $(TOKEN_DIR)/tokenizer.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/type_checkers.o: $(TOKEN_DIR)/type_checkers.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
# Clean rule
clean:
	rm -rf $(LIBDIR)/builtins.o $(LIBDIR)/execute_command.o $(LIBDIR)/get_command_path.o \
	      $(LIBDIR)/input_redirection_herdoc.o $(LIBDIR)/output_redirection_append_mode.o \
	      $(LIBDIR)/piping.o $(LIBDIR)/dup_fd.o $(LIBDIR)/expand.o \
	      $(LIBDIR)/input_redirection.o $(LIBDIR)/output_error_exit.o \
	      $(LIBDIR)/output_redirection.o $(LIBDIR)/parser.o \
	      $(LIBDIR)/tokenizer.o $(LIBDIR)/type_checkers.o \
	      $(LIBDIR)/libft_ft_isalpha.o $(LIBDIR)/libft_ft_isdigit.o $(LIBDIR)/libft_ft_isalnum.o \
	      $(LIBDIR)/libft_ft_isascii.o $(LIBDIR)/libft_ft_isprint.o \
	      $(LIBDIR)/libft_ft_strlen.o $(LIBDIR)/libft_ft_memset.o $(LIBDIR)/libft_ft_bzero.o \
	      $(LIBDIR)/libft_ft_memcpy.o $(LIBDIR)/libft_ft_memmove.o $(LIBDIR)/libft_ft_strlcpy.o \
	      $(LIBDIR)/libft_ft_strlcat.o $(LIBDIR)/libft_ft_toupper.o $(LIBDIR)/libft_ft_tolower.o \
	      $(LIBDIR)/libft_ft_strchr.o $(LIBDIR)/libft_ft_strrchr.o $(LIBDIR)/libft_ft_strncmp.o \
	      $(LIBDIR)/libft_ft_memchr.o $(LIBDIR)/libft_ft_memcmp.o $(LIBDIR)/libft_ft_strnstr.o \
	      $(LIBDIR)/libft_ft_atoi.o $(LIBDIR)/libft_ft_calloc.o $(LIBDIR)/libft_ft_strdup.o \
	      $(LIBDIR)/libft_ft_substr.o $(LIBDIR)/libft_ft_strjoin.o $(LIBDIR)/libft_ft_strtrim.o \
	      $(LIBDIR)/libft_ft_split.o $(LIBDIR)/libft_ft_itoa.o $(LIBDIR)/libft_ft_strmapi.o \
	      $(LIBDIR)/libft_ft_striteri.o $(LIBDIR)/libft_ft_putchar_fd.o $(LIBDIR)/libft_ft_putstr_fd.o \
	      $(LIBDIR)/libft_ft_putendl_fd.o $(LIBDIR)/libft_ft_putnbr_fd.o $(LIBDIR)/libft_get_next_line.o

# Full clean rule
fclean: clean
	rm -rf $(LIBDIR)/libexecution.a $(LIBDIR)/libparsing.a $(LIBDIR)/libtokenization.a $(LIBDIR)/libft.a



