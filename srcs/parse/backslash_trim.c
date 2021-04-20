/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_trim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 12:19:00 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/18 14:14:45 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		trim_len(char *s)
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
		if (s[j] && s[j] != '\\')
			i++;
/*		else if (s[j] == '\\' && (s[j + 1] != '\\' || !s[j + 1]))
			j++;*/
		else if (*s == '\\' && s[j + 1] && s[j + 1] == '\\')
		{
			i++;
			j++;
		}
		q_dq_index(s, j, &q, &dq);
	}
	return (i);
}

static char		*trim_str(char *s)
{
	char	*rtn;
	int		len;
	int		i;
	
	len = trim_len(s);
	if (!(rtn = malloc(sizeof(char) * (len + 1))))
		ft_error();
	i = 0;
	while (*s)
	{
		if (*s && *s != '\\')
			rtn[i++] = *s++;
		else if (*s == '\\' && (*(s + 1) != '\\' || !*(s + 1)))
			s++;
		else if (*s == '\\' && *(s + 1) && *(s + 1) == '\\')
		{
			rtn[i++] = *s++;
			s++;
		}
	}
	rtn[i] = '\0';
	return (rtn);
}

void			backslash_trim(t_ls *data)
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
