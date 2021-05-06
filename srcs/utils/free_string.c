/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:30:43 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/04 12:30:50 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_sys_free(t_ls *data)
{
	data->i = -1;
	while (data->sys.path[++data->i])
		free_string(&data->sys.path[data->i]);
	free_2d_string(&data->sys.path);
	free_string(&data->sys.temp);
	return (data->sys.cmd);
}

void	free_string(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}

void	free_2d_string(char ***s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}
