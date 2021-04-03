/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:53:02 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/03 17:20:37 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		cmd_cnt(char *s, char c)
{
	int	i;
	int	q;
	int	dq;

	i = 0;
	q = 0;
	dq = 0;
	while (*s)
	{
		while (*s && (*s != c || (*s == c && (q == 1 || dq == 1))))
		{
			if (*s == 39)
				(q == 0 && dq == 0) ? (q = 1) : (q = 0);
			if (*s == '"')
				(dq == 0 && q == 0) ? (dq = 1) : (dq = 0);
			s++;
		}
		while (*s && *s == c)
			s++;
		i++;
	}
	return (i);
}

static int		cmd_len(char *s, char c)
{
	int	i;
	int	q;
	int	dq;

	i = 0;
	q = 0;
	dq = 0;
	while (*s && (*s != c || (*s == c && (q == 1 || dq == 1))))
	{
		if (*s == 39)
			(q == 0 && dq == 0) ? (q = 1) : (q = 0);
		if (*s == '"')
			(dq == 0 && q == 0) ? (dq = 1) : (dq = 0);
		s++;
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
	char	**tab;
	int		i;
	int		j;
	int		q;
	int		dq;

	if (!*s || !(tab = malloc(sizeof(char *) * (cmd_cnt(s, c) + 1))))
		return (NULL);
	while (*s && *s == c)
		s++;
	j = 0;
	while (*s)
	{
		i = 0;
		if (!(tab[j] = malloc(sizeof(char) * (cmd_len(s, c) + 1))))
		{
			ft_freee(tab, j);
			return (NULL);
		}
		q = 0;
		dq = 0;
		while (*s && (*s != c || (*s == c && (q == 1 || dq == 1))))
		{
			if (*s == 39)
				(q == 0 && dq == 0) ? (q = 1) : (q = 0);
			if (*s == '"')
				(dq == 0 && q == 0) ? (dq = 1) : (dq = 0);
			tab[j][i++] = *s++;
		}
		tab[j][i] = '\0';
		while (*s && *s == c)
			s++;
		j++;
	}
	tab[j] = 0;
	return (tab);
}
