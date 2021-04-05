/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:22:33 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/05 16:18:31 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sys_call(char **words, t_ls data)
{
	pid_t	pid;
	char	*cmd;

	
	if ((pid = fork()) < 0)
		ft_error();
	if (pid == 0)
	{
		if (!(cmd = ft_strjoin("/bin/", words[0])))
			ft_error();
		if (execve(cmd, words, data.envp) < 0)
			ft_error();
		free(cmd);
	}
	wait(&pid);
}
