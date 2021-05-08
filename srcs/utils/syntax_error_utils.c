/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 19:00:35 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/08 12:33:58 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	second_char_check(t_ls *data, int i)
{
	if (data->line[i] && (data->line[i] == '&' || data->line[i] == '|'
			|| data->line[i] == ';'))
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%c'\n",
			data->line[i]);
		data->statuscode = 2;
		return (1);
	}
	return (0);
}

int	semicolon_comb(t_ls *data)
{
	int	i;
	int	q;
	int	dq;

	i = 0;
	q = 0;
	dq = 0;
	while (data->line[i] && (data->line[i] != ';' || (data->line[i] == ';'
			&& (q == 1 || dq == 1 || prev_bslash(data->line, i, q)))))
		q_dq_index(data->line, i++, &q, &dq);
	if (data->line[i])
		q_dq_index(data->line, i++, &q, &dq);
	if (data->line[i] && data->line[i] == ';')
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token `;;'\n");
		data->statuscode = 2;
		return (1);
	}
	while (data->line[i] && (data->line[i] == ' ' || data->line[i] == '\''
			|| data->line[i] == '"'))
		q_dq_index(data->line, i++, &q, &dq);
	if (second_char_check(data, i))
		return (1);
	return (0);
}

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
			ft_printf_fd
				(2, "minishell: syntax error near unexpected token `|'\n");
			data->statuscode = 2;
			return (1);
		}
	}	
	return (0);
}

int	pipe_comb(t_ls *data)
{
	int	i;
	int	q;
	int	dq;

	i = 0;
	q = 0;
	dq = 0;
	while (data->line[i] && (data->line[i] != '|' || (data->line[i] == '|'
			&& (q == 1 || dq == 1 || prev_bslash(data->line, i, q)))))
		q_dq_index(data->line, i++, &q, &dq);
	if (data->line[i])
		q_dq_index(data->line, i++, &q, &dq);
	if (second_pipe_check(data, i))
		return (1);
	while (data->line[i] && (data->line[i] == ' ' || data->line[i] == '\''
			|| data->line[i] == '"'))
		q_dq_index(data->line, i++, &q, &dq);
	if (data->line[i] && (data->line[i] == '&' || data->line[i] == ';'))
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%c'\n",
			data->line[i]);
		data->statuscode = 2;
		return (1);
	}
	return (0);
}
