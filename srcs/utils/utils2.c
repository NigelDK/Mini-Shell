/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:47:05 by minummin          #+#    #+#             */
/*   Updated: 2021/04/30 11:01:22 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_export(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	j = 0;
	while (i >= j)
	{
		if (s[j] == ' ')
			return (1);
		j++;
	}
	return (0);
}

int	check_spechar(char c)
{
	if (c == '?' || c == '.' || c == ',' || c == '@' || c == '%'
		|| c == '/' || c == '=' || c == '+' || c == '^' || c == '~'
		|| c == '*' || c == '-' || c == ':' || c == '\0' || c == '$'
		|| c == '"' || c == '\\' || c == '\'')
		return (1);
	else if (c == '|')
		return (4);
	else
		return (0);
}

void	ft_envp(t_v *v, char **envp, t_ls *data)
{
	int		i;
	int		process;
	char	*s;

	if (!data) //
		return ; //
	process = 0;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
		{
			process = ft_atoi(ft_strstr_2(envp[i], "=")) + 1;
			s = ft_itoa(process);
			if (!s)
				ft_error();
			v->str = ft_strjoin("SHLVL=", s);
			free(s);
			if (!v->str)
				ft_error();
		}
		else
			v->str = ft_strdup(envp[i]);
		if (!v->str)
			ft_error_v(v);
		v->next = ft_lstnew_2(NULL);
		if (!v->next)
			ft_error_v(v);
		v = v->next;
	}
}

void	ft_minishell_init(t_term *t, t_ls *data, t_v *v)
{
	if (v) //
		return ; //
	t->i = 0;
	t->yo = NULL;
	t->w = NULL;
	t->count = 1;
	tcgetattr(0, &t->term);
	t->term.c_lflag &= ~(ECHO);
	t->term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &t->term);
	t->success = tgetent(NULL, getenv("TERM"));
	if (t->success < 0)
		ft_printf_fd(2, "Could not access the termcap data base.\n");
	if (t->success == 0)
		ft_printf_fd(2, "Terminal type `%s' is not defined.\n", getenv("TERM"));
	data->cd = 0;
	signal(SIGINT, main_signal_handler);
	signal(SIGQUIT, main_signal_handler);
	t->mark = 0;
	g_sigint = 1;
	data->oldpwd = 0;
	data->statuscode = 0;
	t->w = (char **)malloc(sizeof(char *) * (1));
	if (!t->w)
		ft_error();
	t->w[0] = NULL;
	t->errcode = 0;
	data->exp_mark = 0;
}

char	*ft_change_nl(char *s1)
{
	int	i;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\n' && s1[i] != '\0')
		i++;
	s1[i] = '\0';
	return (s1);
}
