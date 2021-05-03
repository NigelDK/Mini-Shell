/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinity_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:23:36 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/03 16:30:49 by minummin         ###   ########.fr       */
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

static int	ft_builtins(t_ls *data, t_v **v, int mark)
{
	if (ft_strcmp_2(data->words2[0], "unset", 1) == 0)
		ft_unset2(data->words2, v, data);
	else if (ft_strcmp_2(data->words2[0], "echo", 1) == 0)
		ft_echo(data->words2);
	else if (ft_strcmp_2(data->words2[0], "cd", 1) == 0)
		data->cd = ft_cd(data->words2, data->cd, data, v);
	else if (ft_strcmp_2(data->words2[0], "pwd", 1) == 0)
		ft_pwd(data->words2);
	else if (ft_strcmp_2(data->words2[0], "export", 1) == 0)
		ft_export(data->words2, *v, data->exp_mark, data);
	else if (ft_strcmp_2(data->words2[0], "env", 1) == 0)
		ft_env(data->words2, *v, data);
	else if (ft_strcmp_2(data->words2[0], "exit", 1) == 0)
		ft_exit(data->words2, v, data);
	else
	{
		mark = 1;
		sys_call(data, v);
	}
	if (data->cd != 0 && data->cd != 1 && data->cd != 2)
		data->cd = 3;
	data->exp_mark = 1;
	return (mark);
}

int	inf_init(t_ls *data)
{
	data->cd = 3;
	data->c_e = NULL;
	data->evm = 0;
	return (0);
}

void	get_statuscode(t_ls *data, int mark)
{
	if (mark == 0 && data->statuscode != 500
		&& data->statuscode != 400)
		data->statuscode = 0;
	if (data->statuscode == 500)
		data->statuscode = 127;
	if (data->statuscode == 400)
		  data->statuscode = 1;
}

void	infinity_loop(t_v **v, char *line, t_ls *data)
{
	int	i;
	int	mark;

	mark = inf_init(data);
	line = ft_change_nl(line);
	if (check_for_redir(v, line, data))
		return ;
	data->words2 = shell_split(line, ' ');
	if (!data->words2)
		ft_error_data_v_2(data, v);
	replace_env_var(data, *v);
	quote_dquote_trim(data);
	backslash_trim(data);
	if (ft_strcmp_2(data->words2[0], "export", 1) == 0 && data->words2[1])
		ft_unset2(data->words2, v, data);
	mark = ft_builtins(data, v, mark);
	get_statuscode(data, mark);
	i = -1;
	while (data->words2[++i])
		free(data->words2[i]);
	if (data->words2)
		free(data->words2);
}
