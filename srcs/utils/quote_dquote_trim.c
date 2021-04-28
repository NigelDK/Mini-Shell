/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dquote_trim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:35:28 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/28 15:44:01 by nde-koni         ###   ########.fr       */
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
	int		i;
	int		j;
	int		q;
	int		dq;

	rtn = malloc(sizeof(char) * (trim_pad_len(s) + 1));
	if (!rtn)
		ft_error();
	d_dq_int_init(&i, &j, &q, &dq);
	while (s[++j])
	{
		if (s[j] == 39 && (dq == 1 || (q == 0 && prev_bslash(s, j, q))))
			rtn[i++] = s[j];
		else if (s[j] == '"' && q == 1)
			rtn[i++] = s[j];
		else if (s[j] == '"' && q == 0 && prev_bslash(s, j, q))
			rtn[i++] = s[j];
		else if (s[j] != 39 && s[j] != '"')
			rtn[i++] = s[j];
		if (s[j] == '\\' && (q == 1 || (dq == 1 && !in_charset(s[j + 1]))))
			rtn[i++] = s[j];
		q_dq_index(s, j, &q, &dq);
	}
	rtn[i] = '\0';
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
		free(data->words2[i]);
		data->words2[i] = tmp;
	}
}
