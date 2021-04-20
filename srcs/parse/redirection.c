/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:48:07 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/20 14:26:24 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_redir_out(char *s, int i)
{
	if ((!s[j - 1] || s[j - 1] != '>') && s[j] == '>' &&
		(!s[j + 1] || s[j + 1] != '>'))
		return (1);
	return (0);
}

static int	is_redir_app(char *s, int i)
{
	if ((!s[j - 1] || s[j - 1] != '>') && s[j] == '>' &&
		s[j + 1] && s[j + 1] == '>' && (!s[j + 2] || s[j + 1] != '>'))
		return (1);
	return (0);
}

static int	is_redir_in(char *s, int i)
{
	if ((!s[j - 1] || s[j - 1] != '<') && s[j] == '<' &&
		(!s[j + 1] || s[j + 1] != '<'))
		return (1);
	return (0);
}

static int  token_len(char *s)
{
	int i;
	int j;
	int q;
	int dq;

	i = 0;
	j = -1;
	q = 0;
	dq = 0;
	while (s[++j])
	{
		i++;
		if (is_redir_out(s, j) && !prev_bslash(s, j, q))
			i = i + 2;
		else if (is_redir_app(s, j) && !prev_bslash(s, j, q))
		{
			i = i + 2;
			j++;
		}
		else if (is_redir_in(s, j) && !prev_bslash(s, j, q))
			i = i + 2;
		q_dq_index(s, j, &q, &dq);
	}
}

static char	tokenizer(char *line, t_ls *data)
{
	int 	len;
	char	*tmp
	int 	i;
	int 	j;
	int 	q;
	int 	dq;

	i = 0;
	j = -1;
	q = 0;
	dq = 0;
	len = token_len(line);
	if (!(tmp = malloc(sizeof(char) * (len + 1))))
		ft_error();
	while (line[++j])
	{
		if (is_redir_out(s, j) && !prev_bslash(s, j, q))
		{
			tmp[i++] = ' ';
			tmp[i++] = line[j];
			tmp[i++] = ' ';
		}
		else if (is_redir_app(s, j) && !prev_bslash(s, j, q))
		{
			tmp[i++] = ' ';
			tmp[i++] = line[j];
			tmp[i++] = line[j + 1];
			tmp[i++] = ' ';
		}
		else if (is_redir_in(s, j) && !prev_bslash(s, j, q))
		{
			tmp[i++] = ' ';
			tmp[i++] = line[j];
			tmp[i++] = ' ';
		}
		q_dq_index(s, j, &q, &dq);
	}
	tmp[i] = '\0';
	if (!(data->words3 = shell_split(line, ' ')))
		ft_error();
	
}
