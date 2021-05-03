/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:32:33 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/03 17:07:12 by nde-koni         ###   ########.fr       */
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
			ft_printf_fd(2, "minishell:  syntax error near unexpected token `");
			while (i-- > 2)
				ft_printf_fd(2, ">");
			ft_printf_fd(2, "'\n");
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
