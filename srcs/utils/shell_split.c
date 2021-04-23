/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:53:02 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/23 14:38:52 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void init_zero(int *i, int *j)
{
	i[0] = 0;
	j[0] = 0;
}

static int		cmd_cnt(char *s, char c)
{
	int	i;
	int	k;
	int	q;
	int	dq;

	i = 0;
	q = 0;
	k = 0;
	dq = 0;
	while (s[k])
	{
		while (s[k] && (s[k] != c || (s[k] == c && (q == 1 || dq == 1)) ||
		(s[k] == c && q == 0 && prev_bslash(s, k, q))))
		{
			q_dq_index(s, k, &q, &dq);
			k++;
		}
		while (s[k] && s[k] == c)
			k++;
		i++;
	}
	return (i);
}

static int		cmd_len(char *s, char c, int k)
{
	int	i;
	int	q;
	int	dq;

	i = 0;
	q = 0;
	dq = 0;
	while (s[k] && (s[k] != c || (s[k] == c && (q == 1 || dq == 1)) ||
	(s[k] == c && q == 0 && prev_bslash(s, k, q))))
	{
		q_dq_index(s, k, &q, &dq);
		k++;
		i++;
	}
	return (i);
}

static void		ft_freee(char **s, int j)
{
	if (j > 0)
	{
		while (j >= 0)
			free(s[j--]);
		free(s); 
	}
}

static char		**fill_tab(char *s, char c, char **tab2)
{
	t_it	i;
	
	init_zero(&i.j, &i.k);
	while (s[i.k])
	{
		i.i = 0;
		if (!(tab2[i.j] = malloc(sizeof(char) * (cmd_len(s, c, i.k) + 1))))
		{
			ft_freee(tab2, i.j);
			tab2 = NULL;
			return (tab2);
		}
		init_zero(&i.q, &i.dq);
		while (s[i.k] && (s[i.k] != c || (s[i.k] == c && (i.q == 1 || i.dq ==
			1)) || (s[i.k] == c && i.q == 0 && prev_bslash(s, i.k, i.q))))
		{
			tab2[i.j][i.i++] = s[i.k];
			q_dq_index(s, i.k++, &i.q, &i.dq);
		}
		tab2[i.j++][i.i] = '\0';
		while (s[i.k] && s[i.k] == c)
			i.k++;
	}
	tab2[i.j] = 0;
	return (tab2);
}

char			**shell_split(char *s, char c)
{
	char	**tab2;

	if (!*s || !(tab2 = malloc(sizeof(char *) * (cmd_cnt(s, c) + 1))))
		return (NULL);
	while (*s && *s == c)
		s++;
	tab2 = fill_tab(s, c, tab2);
	if (tab2 == NULL)
		return (NULL);
	return (tab2);
}
