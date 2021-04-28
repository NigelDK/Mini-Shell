/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 19:00:35 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/28 14:43:21 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	second_pipe_check(t_ls *data, int i)
{
	int	j;

	j = 0;
	if (data->line[i] == ' ')
	{
		j = 0;
		while (data->line[i + j] && data->line[i + j] == ' ')
			j++;
		if (data->line[i + j] && data->line[i + j] == '|')
		{
			printf("bash: syntax error near unexpected token `|'\n");
			data->statuscode = 2;
			return (1);
		}
	}	
	return (0);
}

int	pipe_comb(t_ls *data)
{
	int	i;

	i = 0;
	while (data->line[i] && data->line[i] != '|')
		i++;
	if (data->line[i])
		i++;
	if (second_pipe_check(data, i))
		return (1);
	while (data->line[i] && data->line[i] == ' ')
		i++;
	if (data->line[i] && (data->line[i] == '&' || data->line[i] == ';'))
	{
		printf("bash: syntax error near unexpected token `%c'\n",
		data->line[i]);
		data->statuscode = 2;
		return (1);
	}
	return (0);
}
