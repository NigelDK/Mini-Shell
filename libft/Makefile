# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minummin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/06 11:39:07 by minummin          #+#    #+#              #
#    Updated: 2020/10/06 11:39:11 by minummin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_strlcpy.c \
	ft_strtrim.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstnew.c \
	ft_lstiter.c \
	ft_strstr_rev_2.c \
	ft_strstr_reverse.c \
	ft_strjoin.c \
	ft_substr.c \
	ft_strdup.c \
	ft_calloc.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strlen.c \
	ft_strlcat.c \
	ft_atoi.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strnstr.c \
	ft_strncmp.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strmapi.c \
	ft_itoa.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_split.c

SRCS2 = ft_lstmap_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstnew_bonus.c

OBJECTS = ${SRCS:.c=.o}

OBJECTS2 = ${SRCS2:.c=.o}

HEADERS_FOLDER = includes

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -I${HEADERS_FOLDER}

all: ${NAME}

${NAME}: ${OBJECTS}

	ar rc ${NAME} ${OBJECTS}

bonus: ${OBJECTS2} ${OBJECTS}

	ar rc ${NAME} ${OBJECTS2} ${OBJECTS}

clean:

	${RM} ${OBJECTS2} ${OBJECTS}

fclean: clean

	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
