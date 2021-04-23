/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:00:00 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/23 12:58:26 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_spechar(char c)
{
	if (c == '?' || c == '.' || c == ',' || c == '@' || c == '%'
	|| c == '/' || c == '=' || c == '+' || c == '^' || c == '~'
	|| c == '*' || c == '-' || c == ':' || c == '\0')
		return (1);
	else if (c == '|')
		return (4);
	else 
		return (0);
}

char	*ft_replace(char *word, t_v *v, int j)
{
	char *tmp_begin;
	char *tmp_middle;
	char *tmp_end;
	char *temp;
	char *lol;
	int i;
	int n;
	int res;

	i = 0;
	lol = ft_strdup(word);
	n = j + 1;
	tmp_begin = ft_substr(word, 0, j);
	while (--n >= 0)
		lol++;
	if (ft_isalpha(word[++j]) == 1)
	{
		i++;
		while (ft_isalnum(word[++j]) == 1)
			i++;
	}
	tmp_middle = NULL;
	while (v->next)
	{
		temp = ft_strstr_reverse(v->str, "=");
		if (ft_strncmp(lol, temp, i) == 0)
			tmp_middle = ft_strstr_2(v->str, "=");
		free(temp);
		v = v->next;
	}
	tmp_end = ft_substr(word, j, ft_strlen(word));
	res = check_spechar(tmp_end[0]);
	if (res == 1)
	{
		word = ft_strjoin2(tmp_begin, tmp_middle);
		word = ft_strjoin2(word, tmp_end);
		free(tmp_end);
		return (word);
	}
	else if (res == 4)
	{
		tmp_end++;
		return (tmp_end);
	}
	else
		return (tmp_end);
}

void	replace_env_var(t_ls *data, t_v *v)
{
	int i;
	int	j;
	int	q;
	int	dq;
	char *tmp;

	i = -1;
	while (data->words2[++i])
	{
		j = -1;
		q = 0;
		dq = 0;
		while (data->words2[i][++j])
		{
			if (data->words2[i][j] == '$' && q == 0 && !prev_bslash(data->words2[i], j, q))
			{
				tmp = ft_replace(data->words2[i], v, j);
				free(data->words2[i]);
				data->words2[i] = NULL;
				data->words2[i] = tmp;
				j = 0;
			}
			q_dq_index(data->words2[i], j, &q, &dq);
		}
	}
}
