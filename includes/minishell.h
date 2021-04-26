/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:39:09 by minummin          #+#    #+#             */
/*   Updated: 2021/04/23 14:35:23 by nde-koni         ###   ########.fr       */
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
# include <signal.h>
# include <sys/ioctl.h>
# include <term.h>
# include <termios.h>
# include <termcap.h>
# include <curses.h>

int	g_sigint;

typedef struct s_term
{
	struct termios	term;
	char			*yo;
	int				count;
	char			**w;
	int				i;
	int				success;
	int				l;
	int				mark;
	int				n;
	int				a;
	int				b;
	int				errcode;
}					t_term;

typedef struct s_pipe
{
	int	cmd_cnt;
	int	*pid;
}		t_pipe;

typedef struct s_ls
{
	int		cd;
	char	**envp;
	char	**words;
	char	**words1;
	char	**words2;
	char	**words3;
	char	*temp;
	char	*line;
	int		statuscode;
	char	*lol;
	char	*tmp_begin;
	int		i;
	int		exp_mark;
}			t_ls;

typedef struct s_it
{
	int	i;
	int	j;
	int	k;
	int	q;
	int	dq;
}			t_it;

char			*ft_strstr_2(const char *s1, const char *s2);
char			*ft_strjoin2(char *s1, char *s2);
int				ft_getline(char **line);
int				ft_strcmp_2(const char *s1, const char *s2, int a);
void			ft_exit_success(char **line, char ***words);
void			ft_error_data_v(t_ls *data, t_v *v);
void			ft_error(void);
void			ft_echo(char **words);
void			ft_pwd(char **words);
void			ft_print_prompt(t_ls *data, t_v *v);
void			ft_print_prompt_2(int statuscode);
void			ft_export(char **words, t_v *v, int mark);
int				ft_cd(char **words, int cd, t_ls *data);
void			ft_env(char **words, t_v *v, t_ls *data);
void			sys_call(t_ls *data, t_v **v);
char			**shell_split(char *s, char c);
void			ft_memdel(char *ap);
void			ft_unset(char **words, t_v *v);
void			ft_unset2(char **words, t_v **v);
void			lexer(t_v *v, t_ls *data, char *tester, t_term t);
int				ft_pipe(t_v *v, char *line, t_ls *data);
void			free_fd(int ***fd, int cmd_cnt);
int				tab_cnt(char **tab2);
void			close_fd(int **fd, int cmd_cnt);
void			infinity_loop(t_v **v, char *line, t_ls *data);
void			ft_exit(char **words, t_v **v, t_ls *data);
void			ft_error_v(t_v *v);
void			ft_error_data_v_2(t_ls *data, t_v **v);
void			ft_error_syscall(t_ls *data, t_v **v, char **path, char *temp);
void			ft_error_data_v_child(t_ls *data, t_v **v);
void			free_tab(char ***tab2);
int				redir_out(t_v **v, char *line, t_ls *data);
int				redir_in(t_v **v, char *line, t_ls *data);
void			handler(int signr);
void			cmd_substitution(t_ls *data, t_v **v);
int				ft_print(t_term *t, char *str);
int				ft_putchar(int c);
char			*ft_change_nl(char *s1);
char			**ft_get_w(int *count, int *i, char *yo);
void			ft_putstr(char *s);
void			main_signal_handler(int signr);
void			backslash_trim(t_ls *data);
void			quote_dquote_trim(t_ls *data);
int				prev_bslash(char *s, int k, int q);
void			q_dq_index(char *s, int i, int *q, int *dq);
void			ft_putchar_2(char c);
void			ft_print_prompt_3(int statuscode);
int				redir_out_at_start(char *s);
int				too_many_redir_out(char *s);
void			replace_env_var(t_ls *data, t_v *v);
void			ft_backspace(t_term *t);
char			*ft_get_string(t_term *t, char *str);
void			ft_envp(t_v *v, char **envp);
void			ft_minishell_init(t_term *t, t_ls *data);
int				check_spechar(char c);
void			ft_eof(t_term *t);
void			ft_while_unset(char **words, t_v *v, char *temp);
int				ft_check_export(char *s);

#endif
