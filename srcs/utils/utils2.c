/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin </var/mail/minummin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:47:05 by minummin          #+#    #+#             */
/*   Updated: 2021/04/23 21:47:38 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_spechar(char c)
{
	if (c == '?' || c == '.' || c == ',' || c == '@' || c == '%'
		|| c == '/' || c == '=' || c == '+' || c == '^' || c == '~'
		|| c == '*' || c == '-' || c == ':' || c == '\0' || c == '$')
		return (1);
	else if (c == '|')
		return (4);
	else
		return (0);
}

void	ft_envp(t_v *v, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		v->str = ft_strdup(envp[i]);
		if (!v->str)
			ft_error_v(v);
		v->next = ft_lstnew_2(NULL);
		if (!v->next)
			ft_error_v(v);
		v = v->next;
	}
}

void	ft_minishell_init(t_term *t, t_ls *data)
{
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
		printf("Could not access the termcap data base.\n");
	if (t->success == 0)
		printf("Terminal type `%s' is not defined.\n", getenv("TERM"));
	data->cd = 0;
	signal(SIGINT, main_signal_handler);
	signal(SIGQUIT, main_signal_handler);
	t->mark = 0;
	g_sigint = 1;
	data->statuscode = 0;
	t->w = (char **)malloc(sizeof(char *) * (1));
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
