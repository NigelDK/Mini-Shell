/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:00:00 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/22 21:30:12 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_env_var(t_ls data*, t_v **v)
{
	int i;
	int	j;
	int	q;
	int	dq;
	char *tmp

	i = -1;
	q = 0;
	dq = 0;
	while (data->words2[++i])
	{
		j = -1;
		while (data->words2[i][++j])
		{
			if (data->words2[i][j] == '$')
				tmp =ft_strdup("helloworld");
//				tmp = ft_replace(data->words2[i], v)
			free(data->words2[i]);
			data->words2[i] = tmp;
			q_dq_index(data->words2[i], j, &q, &dq)
		}
	}
}