/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinity_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:23:36 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/27 15:48:53 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_for_redir(t_v **v, char *line, t_ls *data)
{
	if (redir_out(v, line, data))
		return (1);
	if (redir_in(v, line, data))
		return (1);
	return (0);
}
/*
static int	ft_check_variable(t_v *v, char *s)
{
	while (v->next)
	{
		if (ft_strcmp_2(v->str, s, 1) == 0)
			return (1);
		v = v->next;
	}
	return (0);
}*/
static int	ft_builtins(t_ls *data, t_v **v, int mark)
{
//	int i;
//
//	i = 0;
//	if (ft_strcmp_2(data->words2[0], "export", 1) == 0)
//	{
/*		while (data->words2[++i])
		{
			if (ft_strcmp_2(data->words2[0], "export", 1) == 0 && ft_check_variable(*v, data->words2[i]) == 1)
				printf("HHH\n");
		}*/
//	}
	if (ft_strcmp_2(data->words2[0], "unset", 1) == 0)
		ft_unset2(data->words2, v, data);
	else if (ft_strcmp_2(data->words2[0], "echo", 1) == 0)
		ft_echo(data->words2);
	else if (ft_strcmp_2(data->words2[0], "cd", 1) == 0)
		data->cd = ft_cd(data->words2, data->cd, data);
	else if (ft_strcmp_2(data->words2[0], "pwd", 1) == 0)
		ft_pwd(data->words2);
	else if (ft_strcmp_2(data->words2[0], "export", 1) == 0)
		ft_export(data->words2, *v, data->exp_mark);
	else if (ft_strcmp_2(data->words2[0], "env", 1) == 0)
		ft_env(data->words2, *v, data);
	else if (ft_strcmp_2(data->words2[0], "exit", 1) == 0)
		ft_exit(data->words2, v, data);
	else
	{
		mark = 1;
		sys_call(data, v);
	}
	data->exp_mark = 1;
	return (mark);
}

void	infinity_loop(t_v **v, char *line, t_ls *data)
{
	int	i;
	int	mark;

	mark = 0;
	data->evm = 0;
	line = ft_change_nl(line);
	if (check_for_redir(v, line, data))
		return ;
	data->words2 = shell_split(line, ' ');
	if (!data->words2)
		ft_error_data_v_2(data, v);
	replace_env_var(data, *v);
	quote_dquote_trim(data);
	backslash_trim(data);
	if (ft_strcmp_2(data->words2[0], "export", 1) == 0)
		ft_unset2(data->words2, v, data);
	if (data->evm != 1)
		mark = ft_builtins(data, v, mark);
	if (mark == 0 && data->statuscode != 500)
		data->statuscode = 0;
	if (data->statuscode == 500)
		data->statuscode = 127;
	i = -1;
	while (data->words2[++i])
		free(data->words2[i]);
	if (data->words2)
		free(data->words2);
}
