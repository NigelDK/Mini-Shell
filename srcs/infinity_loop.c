/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinity_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:23:36 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/05 16:26:32 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	infinity_loop(t_v **v, char *line, int *cd, t_ls data)
{
	int		i;
	char	**words;
	char	*temp;

	temp = ft_strstr_reverse((*v)->str, "=");
	if (!(words = shell_split(line, ' ')))
		ft_error_split(&line, &words);
	if (ft_strcmp_2(words[0], "echo", 1) == 0)
		ft_echo(words, line, *v);
	else if (ft_strcmp_2(words[0], "cd", 1) == 0)
		cd[0] = ft_cd(words, *cd);
	else if (ft_strcmp_2(words[0], "pwd", 1) == 0)
		ft_pwd(words);
	else if (ft_strcmp_2(words[0], "export", 1) == 0)
		ft_export(words, *v);
	else if (ft_strcmp_2(words[0], "env", 1) == 0)
		ft_env(words, *v);
	else if (ft_strcmp_2(words[0], "unset", 1) == 0
	&& ft_strcmp_2(words[1], temp, 1) == 0)
		ft_unset2(words, v);
	else if (ft_strcmp_2(words[0], "unset", 1) == 0)
		ft_unset(words, *v);
	else if (ft_strcmp_2(words[0], "exit", 1) == 0)
		ft_exit(words, v, temp);
	else
		sys_call(words, data);
	i = -1;
	while (words[++i])
		free(words[i]);
	free(words);
	free(temp);
}
