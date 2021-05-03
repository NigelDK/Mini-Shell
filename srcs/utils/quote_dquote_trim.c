/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dquote_trim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:35:28 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/03 17:31:55 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	d_dq_int_init(int *i, int *j, int *q, int *dq)
{
	i[0] = 0;
	j[0] = -1;
	q[0] = 0;
	dq[0] = 0;
}

int	in_charset(char c)
{
	if (!c)
		return (0);
	if (c == '$')
		return (1);
	if (c == '\\')
		return (1);
	return (0);
}

int	trim_pad_len(char *s)
{
	int	i;
	int	j;
	int	q;
	int	dq;

	d_dq_int_init(&i, &j, &q, &dq);
	while (s[++j])
	{
		if (s[j] == 39 && q == 0 && (dq == 1 || prev_bslash(s, j, q)))
			i++;
		else if (s[j] == '"' && q == 1)
			i++;
		else if (s[j] == '"' && q == 0 && prev_bslash(s, j, q))
			i++;
		else if (s[j] != 39 && s[j] != '"')
			i++;
		else if (s[j] == 39 && dq == 1)
			i++;
		if (s[j] == '\\' && (q == 1 || (dq == 1 && !in_charset(s[j + 1]))))
			i++;
		q_dq_index(s, j, &q, &dq);
	}
	return (i);
}

char	*d_dq_trim_pad_str(char *s)
{
	char	*rtn;
	t_it	l;

	rtn = malloc(sizeof(char) * (trim_pad_len(s) + 1));
	if (!rtn)
		return (NULL);
	d_dq_int_init(&l.i, &l.j, &l.q, &l.dq);
	while (s[++l.j])
	{
		if (s[l.j] == 39 && (l.dq == 1
				|| (l.q == 0 && prev_bslash(s, l.j, l.q))))
			rtn[l.i++] = s[l.j];
		else if (s[l.j] == '"' && l.q == 1)
			rtn[l.i++] = s[l.j];
		else if (s[l.j] == '"' && l.q == 0 && prev_bslash(s, l.j, l.q))
			rtn[l.i++] = s[l.j];
		else if (s[l.j] != 39 && s[l.j] != '"')
			rtn[l.i++] = s[l.j];
		if (s[l.j] == '\\' && (l.q == 1
				|| (l.dq == 1 && !in_charset(s[l.j + 1]))))
			rtn[l.i++] = s[l.j];
		q_dq_index(s, l.j, &l.q, &l.dq);
	}
	rtn[l.i] = '\0';
	return (rtn);
}

/*
** The quotes and double quotes get trimmed from the string.
** Simultaneously the backslashes that aren't escape characters
** get padded with extra backslash so backslash_trim doesn't
** trim them.
** Inefficient coding because of layering a fix on top of a fix.
*/

void	quote_dquote_trim(t_ls *data)
{
	int		i;
	char	*tmp;

	i = -1;
	while (data->words2[++i])
	{
		tmp = d_dq_trim_pad_str(data->words2[i]);
		if (!tmp)
			ft_error();
		free(data->words2[i]);
		data->words2[i] = tmp;
	}
}
