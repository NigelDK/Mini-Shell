/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinity_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:23:36 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/22 18:55:27 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		check_for_redir(t_v **v, char *line, t_ls *data)
{
	if (redir_out(v, line, data))
		return (1);
	if (redir_in(v, line, data))
		return (1);
	return (0);
}

void			infinity_loop(t_v **v, char *line, t_ls *data)
{
	int		i;
	int		mark;

	mark = 0;
	line = ft_change_nl(line);
	data->temp = ft_strstr_reverse((*v)->str, "=");
	if (check_for_redir(v, line, data))
		return ;
	if (!(data->words2 = shell_split(line, ' ')))
		ft_error_data_v_2(data, v);
	replace_env_var(data, *v);
	quote_dquote_trim(data);
	backslash_trim(data);
	if (ft_strcmp_2(data->words2[0], "echo", 1) == 0)
		ft_echo(data->words2, *v, data->statuscode);
	else if (ft_strcmp_2(data->words2[0], "cd", 1) == 0)
		data->cd = ft_cd(data->words2, data->cd);
	else if (ft_strcmp_2(data->words2[0], "pwd", 1) == 0)
		ft_pwd(data->words2);
	else if (ft_strcmp_2(data->words2[0], "export", 1) == 0)
		ft_export(data->words2, *v);
	else if (ft_strcmp_2(data->words2[0], "env", 1) == 0)
		ft_env(data->words2, *v);
	else if (ft_strcmp_2(data->words2[0], "unset", 1) == 0
	&& ft_strcmp_2(data->words2[1], data->temp, 1) == 0)
		ft_unset2(data->words2, v);
	else if (ft_strcmp_2(data->words2[0], "unset", 1) == 0)
		ft_unset(data->words2, *v);
	else if (ft_strcmp_2(data->words2[0], "exit", 1) == 0)
		ft_exit(data->words2, v, data->temp);
	else
	{
		mark = 1;
		sys_call(data, v);
	}
	if (mark == 0)
		data->statuscode = 0;
	i = -1;
	while (data->words2[++i])
		free(data->words2[i]);
	if (data->words2)
		free(data->words2);
	free(data->temp);
}
