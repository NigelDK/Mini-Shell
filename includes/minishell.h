/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:39:09 by minummin          #+#    #+#             */
/*   Updated: 2021/04/05 16:24:14 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <locale.h>
# include <wchar.h>

typedef struct	s_ls
{
	int	cd;
	char	**envp;
	char	**words;
	char	**words2;
	char	*temp;
	char	*line;
}				t_ls;

char	*ft_strstr_2(const char *s1, const char *s2);
char	*ft_strjoin2(char *s1, char *s2);
int		ft_getline(char **line);
int		ft_strcmp_2(const char *s1, const char *s2, int a);
void	ft_exit_success(char **line, char ***words);
void	ft_error_data_v(t_ls *data, t_v *v);
void	ft_error(void);
void	ft_echo(char **words, char *line, t_v *v);
void	ft_pwd(char **words);
void	ft_print_prompt(int cd, t_v *v);
void	ft_print_prompt_2(void);
void	ft_export(char **words, t_v *v);
int		ft_cd(char **words, int cd);
void 	ft_env(char **words, t_v *v);
void	sys_call(t_ls *data, t_v **v);
char	**shell_split(char *s, char c);
void	ft_memdel(char *ap);
void	ft_unset(char **words, t_v *v);
void	ft_unset2(char **words, t_v **v);
void	lexer(t_v *v, t_ls *data);
int		ft_pipe(t_v *v, char *line, t_ls *data);
void	infinity_loop(t_v **v, char *line, t_ls *data);
void	ft_exit(char **words, t_v **v, char *temp);
void	ft_error_v(t_v *v);
void	ft_error_data_v_2(t_ls *data, t_v **v);
void	ft_error_syscall(t_ls *data, t_v **v, char **path, char *temp);
void	ft_error_data_v_child(t_ls *data, t_v **v);

#endif
