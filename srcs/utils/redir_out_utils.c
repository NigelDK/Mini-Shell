/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:32:33 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/28 14:02:23 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	too_many_redir_out(char *s)
{
	int	i;

	while (*s)
	{
		i = 0;
		while (*s == '>')
		{
			i++;
			s++;
		}
		if (i > 2)
		{
			printf("bash:  syntax error near unexpected token `");
			while (i-- > 2)
				printf(">");
			printf("'\n");
			return (1);
		}
		(i == 0) ? (s++) : (0);
	}
	return (0);
}

int	redir_out_at_start(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '>')
		return (1);
	return (0);
}
