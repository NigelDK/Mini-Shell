NAME = libftminishell.a

SRCS = srcs/main.c \
	srcs/error_free.c \
	srcs/print_prompt.c \
	srcs/get_line.c \
	srcs/echo.c \
	srcs/utils.c \
	srcs/cd.c \
	srcs/pwd.c \
	srcs/export.c \
	srcs/env.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	libft/ft_lstsize.c \
	libft/ft_lstdelone.c \
	libft/ft_lstclear.c \
	libft/ft_lstiter.c \
	libft/ft_lstnew.c \
	libft/ft_strstr_rev_2.c \
	libft/ft_strstr_reverse.c \
	libft/ft_strlcpy.c \
        libft/ft_strtrim.c \
        libft/ft_strjoin.c \
        libft/ft_substr.c \
        libft/ft_strdup.c \
        libft/ft_calloc.c \
        libft/ft_memset.c \
        libft/ft_bzero.c \
        libft/ft_memcpy.c \
        libft/ft_memccpy.c \
        libft/ft_memmove.c \
        libft/ft_memchr.c \
        libft/ft_memcmp.c \
        libft/ft_strlen.c \
        libft/ft_strlcat.c \
        libft/ft_atoi.c \
        libft/ft_strchr.c \
        libft/ft_strrchr.c \
        libft/ft_strnstr.c \
        libft/ft_strncmp.c \
        libft/ft_isalpha.c \
        libft/ft_isdigit.c \
        libft/ft_isalnum.c \
        libft/ft_isascii.c \
        libft/ft_isprint.c \
        libft/ft_toupper.c \
        libft/ft_tolower.c \
        libft/ft_strmapi.c \
        libft/ft_itoa.c \
        libft/ft_putchar_fd.c \
        libft/ft_putstr_fd.c \
        libft/ft_putendl_fd.c \
        libft/ft_putnbr_fd.c \
        libft/ft_split.c

OBJECTS = ${SRCS:.c=.o}

HEADERS_FOLDER = includes

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -I${HEADERS_FOLDER}

all: ${NAME}

${NAME}: ${OBJECTS}

	ar rc ${NAME} ${OBJECTS}
	gcc libftminishell.a -o minishell

clean:

	${RM} ${OBJECTS}

fclean: clean

	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
