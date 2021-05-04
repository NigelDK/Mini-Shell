/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:39:09 by minummin          #+#    #+#             */
/*   Updated: 2021/05/03 23:57:36 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_printf_err/printf.h"
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
	int				cmd_cnt;
	int				*pid;
	int				i;
	int				**fd;
}					t_pipe;

typedef struct s_ro
{
	int		*fd;
	char	**filename;
}			t_ro;

typedef struct s_ri
{
	int		*fd;
	char	**filename;
}			t_ri;

typedef struct s_bt
{
	char	*tmp;
	char	*rtn;
}				t_bt;

typedef struct s_exp
{
	char	**words;
}		t_exp;

typedef struct s_sys
{
	char	**path;
	char	*temp;
	char	*cmd;
}		t_sys;

typedef struct s_un
{
	char	*tmp;
	char	*temp;
}		t_un;

typedef struct s_un2
{
	char	*tmp;
	char	*temp;
}		t_un2;

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
	int		evm;
	char	*c_e;
	int		oldpwd;
	t_ro	ro;
	t_pipe	p;
	t_ri	ri;
	t_bt	bt;
	t_exp	exp;
	t_sys	sys;
	t_un	un;
	t_un2	un2;
}			t_ls;

typedef struct s_it
{
	int	i;
	int	j;
	int	k;
	int	q;
	int	dq;
}			t_it;

void			ft_newpwd(t_v *v, char *str);
void			ft_oldpwd(t_v *v);
char			*ft_strstr_2(const char *s1, const char *s2);
char			*ft_strjoin2(char *s1, char *s2);
int				ft_getline(char **line);
int				ft_strcmp_2(const char *s1, const char *s2, int a);
void			ft_exit_success(char **line, char ***words);
void			ft_error_data_v(t_ls *data, t_v *v);
void			ft_error(void);
void			ft_echo(char **words);
void			ft_pwd(t_ls *data, t_v **v);
void			ft_print_prompt(t_ls *data, t_v *v);
void			ft_print_prompt_2(int statuscode);
void			ft_export(char **words, t_v *v, int mark, t_ls *data);
int				ft_cd(char **words, int cd, t_ls *data, t_v **v);
void			ft_env(char **words, t_v *v, t_ls *data);
void			sys_call(t_ls *data, t_v **v);
char			**shell_split(char *s, char c);
void			ft_memdel(char *ap);
void			ft_unset(char **words, t_v *v);
void			ft_unset2(char **words, t_v **v, t_ls *data);
void			lexer(t_v *v, t_ls *data, t_term t);
int				ft_pipe(t_v *v, char **line, t_ls *data);
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
void			ft_envp(t_v *v, char **envp, t_ls *data);
void			ft_minishell_init(t_term *t, t_ls *data, t_v *v);
int				check_spechar(char c);
void			ft_eof(t_term *t);
void			ft_while_unset(char **words, t_v *v, t_ls *data);
int				ft_check_export(char *s);
int				syntax_error_check(t_ls *data);
int				pipe_comb(t_ls *data);
void			d_dq_int_init(int *i, int *j, int *q, int *dq);
int				in_charset(char c);
int				d_dq_trim_pad_len(char *s);
char			*d_dq_trim_pad_str(char *s);
char			*bslash_trim_str(char *s);
int				bslash_trim_len(char *s);
void			redir_trim(t_ls *data, char *line);
void			unset_export(char **words, t_ls *data, t_v **v);
int				shell_split_cmd_cnt(char *s, char c);
void			init_zero(int *i, int *j);
void			trim_filename(t_ls *data);
void			tester_lexer(t_v *v, t_ls *data, t_term t, char **argv);
void			ft_create_env(t_v *v, char *str, t_ls *data);
int				change_home(t_ls *data, int i, t_v *v);
void			free_string(char **s);
void			free_2d_string(char ***s);
void			free_int(int **i);
void			free_tab_int(int ***i);
void			ft_free_all(t_ls *data, t_v **v);

#endif
