/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinity_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:23:36 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/09 20:35:31 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		quote_double_quote(t_ls *data, t_v **v)
{
	int		i;
	char	**tmp;

	i = -1;
	while (data->words2[++i])
	{
		if (data->words2[i][0] == 39 /*|| data->words2[i][0] == '"'*/)
		{
			if (data->words2[i][0] == 39)
			{
				if (!(tmp = ft_split(data->words2[i], 39)))
					ft_error_data_v_2(data, v);
			}
//			else if (data->words2[i][0] == '"')
//			{
//				if (!(tmp = ft_split(data->words2[i], '"')))
//					ft_error_data_v_2(data, v);
//				printf("%s: %li\n", data->words2[i], ft_strlen(data->words2[i]));
//			}
			free(data->words2[i]);
			data->words2[i] = tmp[0];
			free(tmp[1]);
			free(tmp);
		}
	}
}

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

	data->temp = ft_strstr_reverse((*v)->str, "=");
	if (check_for_redir(v, line, data))
		return ;
	if (!(data->words2 = shell_split(line, ' ')))
		ft_error_data_v_2(data, v);
//	cmd_substitution(data, v);
	quote_double_quote(data, v);
	if (ft_strcmp_2(data->words2[0], "echo", 1) == 0)
		ft_echo(data, data->words2, line, *v);
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
		sys_call(data, v);
	i = -1;
	while (data->words2[++i])
		free(data->words2[i]);
	if (data->words2)
		free(data->words2);
	free(data->temp);
}
