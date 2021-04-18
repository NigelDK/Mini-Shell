/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_dquote_trim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:35:28 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/18 11:11:08 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	q_dq_index(char *s, int i, int *q, int *dq)
{
	if (s[i] == 39)
	{
		if (dq[0] == 1 || (q[0] == 0 && prev_bslash(s, i, *q)))
			q[0] = q[0];
		else if (q[0] == 0 && dq[0] == 0 && !prev_bslash(s, i, *q))
			q[0] = 1;
		else if (q[0] == 1)
			q[0] = 0;
	}
	if (s[i] == '"')
	{
		if (q[0] == 1 || prev_bslash(s, i, *q))
			dq[0] = dq[0];
		else if (dq[0] == 0 && q[0] == 0 && !prev_bslash(s, i, *q))
			dq[0] = 1;
		else if (dq[0] == 1 && q[0] == 0 && !prev_bslash(s, i, *q))
			dq[0] = 0;
	}
}

static int	trim_len(char *s)
{
	int	i;
	int	j;
	int	q;
	int	dq;

	i = 0;
	j = -1;
	q = 0;
	dq = 0;
	while (s[++j])
	{
/*		if (s[j] == 39)
		{
			if (dq == 1 || (q == 0 && prev_bslash(s, j, q)))
				q = q;
			else if (q == 0 && dq == 0 && !prev_bslash(s, j, q))
				q = 1;
			else if (q == 1)
				q = 0;
		}
		if (s[j] == '"')
		{
			if (q == 1 || prev_bslash(s, j, q))
				dq = dq;
			else if (dq == 0 && q == 0 && !prev_bslash(s, j, q))
				dq = 1;
			else if (dq == 1 && q == 0 && !prev_bslash(s, j, q))
				dq = 0;
		}*/
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
		q_dq_index(s, j, &q, &dq);
	}
	return (i);
}

static char	*trim_str(char *s)
{
	char	*rtn;
	int		len;
	int		i;
	int		j;
	int		q;
	int		dq;

	len = trim_len(s);
	if (!(rtn = malloc(sizeof(char) * (len + 1))))
		ft_error();
	i = 0;
	j = 0;
	q = 0;
	dq = 0;
	while (s[j])
	{
/*		if (s[j] == 39)
		{
			if (dq == 1 || (q == 0 && prev_bslash(s, j, q)))
				q = q;
			else if (q == 0 && dq == 0 && !prev_bslash(s, j, q))
				q = 1;
			else if (q == 1)
				q = 0;
		}
		if (s[j] == '"')
		{
			if (q == 1 || prev_bslash(s, j, q))
				dq = dq;
			else if (dq == 0 && q == 0 && !prev_bslash(s, j, q))
				dq = 1;
			else if (dq == 1 && q == 0 && !prev_bslash(s, j, q))
				dq = 0;
		}*/
		if (s[j] == 39 && (dq == 1 || (q == 0 && prev_bslash(s, j, q))))
			rtn[i++] = s[j];
		else if (s[j] == '"' && q == 1)
			rtn[i++] = s[j];
		else if (s[j] == '"' && q == 0 && prev_bslash(s, j, q))
			rtn[i++] = s[j];
		else if (s[j] != 39 && s[j] != '"')
			rtn[i++] = s[j];
		q_dq_index(s, j, &q, &dq);
		j++;
//		printf("%i || %i\n", q, dq); //testing
	}
	rtn[i] = '\0';
	return (rtn);
}

void		quote_dquote_trim(t_ls *data)
{
	int		i;
	char	*tmp;

	i = -1;
	while (data->words2[++i])
	{
		tmp = trim_str(data->words2[i]);
		free(data->words2[i]);
		data->words2[i] = tmp;
	}
}
