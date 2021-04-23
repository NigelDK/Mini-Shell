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

char	*ft_replace(char *word, t_v *v, int j)
{
	char *tmp_begin;
	char *tmp_middle;
	char *tmp_end;
	char *temp;
	char *lol;
	int i;
	int n;

	i = 0;
	lol = ft_strdup(word);
	n = j;
	if (!v)
		return (NULL);
	tmp_begin = ft_substr(word, 0, j);
	while (n >= 0)
	{
		lol++;
		n--;
	}
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
	word = ft_strjoin2(tmp_begin, tmp_middle);
	word = ft_strjoin2(word, tmp_end);
//	printf("tmp_begin = %s\n", tmp_begin);
//	printf("tmp_middle = %s\n", tmp_middle);
//	printf("tmp_end = %s\n", tmp_end);
	return (word);
//	return (ft_strjoin2(ft_strjoin2(tmp_begin, tmp_middle), tmp_end));
}

void	replace_env_var(t_ls *data, t_v *v)
{
	int i;
	int	j;
	int	q;
	int	dq;
	char *tmp;

	i = -1;
	if (!v)
		return ;
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
		//		printf("tmp = %s\n", tmp);
		//		printf("words = %s\n", data->words2[i]);
				break ;
			}
			q_dq_index(data->words2[i], j, &q, &dq);
		}
	}
}
