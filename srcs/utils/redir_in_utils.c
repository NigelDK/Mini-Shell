/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 13:20:28 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/08 13:28:23 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error_check(int i)
{
	if (i > 1)
	{
		ft_printf_fd(2, "bash:  syntax error near unexpected token `");
		while (i-- > 1)
			printf("<");
		printf("'\n");
		return (1);
	}
	return (0);
}

int	too_many_redir_in(char *s)
{
	int	i;
	int	j;
	int	q;
	int	dq;

	j = 0;
	q = 0;
	dq = 0;
	while (s[j])
	{
		i = 0;
		while (s[j] == '<' && q == 0 && dq == 0 && !prev_bslash(s, j, q))
		{
			i++;
			q_dq_index(s, j++, &q, &dq);
		}
		if (error_check(i))
			return (1);
		if (i == 0)
			q_dq_index(s, j++, &q, &dq);
	}
	return (0);
}
