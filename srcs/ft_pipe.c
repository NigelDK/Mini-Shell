/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:49:09 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/05 16:40:47 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		tab_cnt(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int			ft_pipe(t_v *v, char *line, int *cd, t_ls data)
{
	int		fd[2];
	int		pid[2];
	int		cmd_cnt;
	char	**cmds;
	
	if (!(cmds = shell_split(line, '|')))
		ft_error_split(&line, &cmds);
	cmd_cnt = tab_cnt(cmds);
	if (cmd_cnt == 1)
		return (0);
	if (pipe(fd) == -1)
		ft_error();
	if ((pid[0] = fork()) < 0)
		ft_error();
	if (pid[0] == 0)
	{
		if (dup2(fd[1], 1) == -1)
			ft_error();
		close(fd[0]);
		close(fd[1]);
		infinity_loop(v, cmds[0], cd, data);
	}
	if ((pid[1] = fork()) < 0)
		ft_error();
	if (pid[1] == 0)
	{
		if (dup2(fd[0], 0) == -1)
			ft_error();
		close(fd[0]);
		close(fd[1]);
		infinity_loop(v, cmds[1], cd, data);
	}
	close(fd[0]);
	close(fd[1]);
	wait(&pid[0]);
	wait(&pid[1]);
	return (1);
}
