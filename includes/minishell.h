#ifndef MINISHELL_H
# define MINISHELL_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

char	*ft_strstr_2(const char *s1, const char *s2);
char	*ft_strjoin2(char *s1, char *s2);
int	ft_getline(char **line);
int	ft_strcmp_2(const char *s1, const char *s2, int a);
void	ft_exit_success(char **line, char ***words);
void	ft_error_split(char **line, char ***words);
void	ft_error(void);
void	ft_echo(char **words, char *line, t_v *v);
void	ft_pwd(void);
void	ft_print_prompt(int cd);
void	ft_print_prompt_2(void);
void	ft_export(char **words, t_v *v);
int	ft_cd(char **words, int cd);

#endif
