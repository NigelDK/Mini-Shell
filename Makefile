NAME = libftminishell.a

SRCS = srcs/main.c \
	srcs/cmds/echo.c \
	srcs/cmds/cd.c \
	srcs/cmds/exit.c \
	srcs/cmds/unset.c \
	srcs/cmds/pwd.c \
	srcs/cmds/export.c \
	srcs/cmds/env.c \
	srcs/cmds/sys_call.c \
	srcs/cmds/signal_handlers.c \
	srcs/parse/lexer.c \
	srcs/parse/ft_pipe.c \
	srcs/parse/infinity_loop.c \
	srcs/parse/get_line.c \
	srcs/parse/redir_out.c \
	srcs/parse/redir_in.c \
	srcs/parse/replace_env_var.c \
	srcs/utils/error_free.c \
	srcs/utils/print_prompt.c \
	srcs/utils/utils.c \
	srcs/utils/utils2.c \
	srcs/utils/shell_split.c \
	srcs/utils/free_tab.c \
	srcs/utils/ft_pipe_utils.c \
	srcs/utils/tab_cnt.c \
	srcs/utils/quote_dquote_trim.c \
	srcs/utils/backslash_trim.c \
	srcs/utils/prev_bslash.c \
	srcs/utils/q_dq_index.c \
	srcs/utils/redir_out_utils.c \
	srcs/termcap/print_termcap.c \
	srcs/termcap/termcap_utils.c \
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

CFLAGS = -Wall -Wextra -Werror -I${HEADERS_FOLDER} -g

all: ${NAME}

${NAME}: ${OBJECTS}

	ar rc ${NAME} ${OBJECTS}
	gcc -g libftminishell.a -ltermcap -lncurses -o minishell

clean:

	${RM} ${OBJECTS}

fclean: clean

	${RM} ${NAME}
	rm minishell

re: fclean all

.PHONY: all clean fclean re
