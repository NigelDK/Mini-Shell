/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:48:07 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/29 12:39:24 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	start_check(t_ls *data)
{
	int	i;

	i = 0;
	while (data->line[i] && data->line[i] == ' ')
		i++;
	if (data->line[i] && (data->line[i] == '|' || data->line[i] == ';'))
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%c'\n",
			data->line[i]);
		data->statuscode = 2;
		return (1);
	}
	return (0);
}

static int	semicolon_comb(t_ls *data)
{
	int	i;

	i = 0;
	while (data->line[i] && data->line[i] != ';')
		i++;
	if (data->line[i])
		i++;
	if (data->line[i] && data->line[i] == ';')
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token `;;'\n");
		data->statuscode = 2;
		return (1);
	}
	while (data->line[i] && data->line[i] == ' ')
		i++;
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

static int	newline_err(t_ls *data, int i)
{
	if (data->line[i] && data->line[i] == '\n')
	{
		ft_printf_fd(2, "bash: syntax error near unexpected token `newline'\n");
		data->statuscode = 2;
		return (1);
	}
	return (0);
}

static int	big_small_than_comb(t_ls *data)
{
	int	i;

	i = 0;
	while (data->line[i] && data->line[i] != '<' && data->line[i] != '>')
		i++;
	if (data->line[i])
		i++;
	while (data->line[i] && data->line[i] == ' ')
		i++;
	if (newline_err(data, i))
		return (1);
	if (data->line[i] && (data->line[i] == '&' || data->line[i] == ';'
			|| data->line[i] == '<' || (data->line[i] == '>'
			&& data->line[i - 1] != '>') || data->line[i] == '|'))
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%c'\n",
			data->line[i]);
		data->statuscode = 2;
		return (1);
	}
	return (0);
}

int	syntax_error_check(t_ls *data)
{
	if (start_check(data))
		return (1);
	if (semicolon_comb(data))
		return (1);
	if (pipe_comb(data))
		return (1);
	if (big_small_than_comb(data))
		return (1);
	return (0);
}
