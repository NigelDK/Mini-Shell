/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:32:33 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/29 12:25:12 by nde-koni         ###   ########.fr       */
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
			ft_printf_fd(2, "bash:  syntax error near unexpected token `");
			while (i-- > 2)
				printf(">");
			printf("'\n");
			return (1);
		}
		if (i == 0)
			s++;
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

void	trim_filename(char **filename)
{
	char	*tmp;

	tmp = d_dq_trim_pad_str(filename[0]);
	free(filename[0]);
	filename[0] = tmp;
	tmp = bslash_trim_str(filename[0]);
	free(filename[0]);
	filename[0] = tmp;
}
