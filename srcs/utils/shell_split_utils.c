/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:25:35 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/28 17:27:53 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_zero(int *i, int *j)
{
	i[0] = 0;
	j[0] = 0;
}

int	shell_split_cmd_cnt(char *s, char c)
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
		while (s[k] && (s[k] != c || (s[k] == c && (q == 1 || dq == 1))
				|| (s[k] == c && q == 0 && prev_bslash(s, k, q))))
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
