/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:53:02 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/22 20:02:02 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void init_int(int *i, int *j)
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

char			**shell_split(char *s, char c)
{
	char	**tab2;
	int		i;
	int		j;
	int		k;
	int		q;
	int		dq;

	if (!*s || !(tab2 = malloc(sizeof(char *) * (cmd_cnt(s, c) + 1))))
		return (NULL);
	while (*s && *s == c)
		s++;
	init_int(&j, &k);
//	j = 0;
//	k = 0;
	while (s[k])
	{
		i = 0;
		if (!(tab2[j] = malloc(sizeof(char) * (cmd_len(s, c, k) + 1))))
		{
			ft_freee(tab2, j);
			return (NULL);
		}
		init_int(&q, &dq);
//		q = 0;
//		dq = 0;
		while (s[k] && (s[k] != c || (s[k] == c && (q == 1 || dq == 1)) ||
		(s[k] == c && q == 0 && prev_bslash(s, k, q))))
		{
			tab2[j][i++] = s[k];
			q_dq_index(s, k++, &q, &dq);
		}
		tab2[j++][i] = '\0';
		while (s[k] && s[k] == c)
			k++;
	}
	tab2[j] = 0;
	return (tab2);
}
