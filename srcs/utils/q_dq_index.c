/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_dq_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 12:57:08 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/19 14:30:51 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	q_dq_index(char *s, int i, int *q, int *dq)
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
