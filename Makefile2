NAME = libftprintf.a

SRCS = ft_print_s2.c \
	ft_print_s.c \
	ft_print_p.c \
	ft_print_p2.c \
	ft_print_cux_and_add_struct2.c \
	ft_print_d.c \
	ft_print_d2.c \
	ft_output.c \
	ft_add_struct.c \
	ft_itoa.c \
	ft_printf.c

OBJECTS = ${SRCS:.c=.o}

HEADERS_FOLDER = includes

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -I${HEADERS_FOLDER}

all: ${NAME}

${NAME}: ${OBJECTS}

	ar rc ${NAME} ${OBJECTS}

clean:

	${RM} ${OBJECTS}

fclean: clean

	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
