/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:32:33 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/04 11:46:07 by nde-koni         ###   ########.fr       */
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

void	trim_filename(t_ls *data, t_v **v)
{
	char	*tmp;

	tmp = d_dq_trim_pad_str(data->ro.filename[0]);
	if (!tmp)
		ft_error(data, v);
	free(data->ro.filename[0]);
	data->ro.filename[0] = tmp;
	tmp = bslash_trim_str(data->ro.filename[0]);
	if (!tmp)
		ft_error(data, v);
	free(data->ro.filename[0]);
	data->ro.filename[0] = tmp;
}
