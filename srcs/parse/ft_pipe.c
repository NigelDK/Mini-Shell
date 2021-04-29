/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:49:09 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/29 09:37:57 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	pipes_and_pids(int ***fd, int **pid, int cmd_cnt)
{
	int	i;
	int	err;

	fd[0] = malloc(sizeof(int *) * (cmd_cnt - 1));
	if (!fd[0])
		ft_error();
	i = -1;
	while (++i < cmd_cnt - 1)
	{
		fd[0][i] = malloc(sizeof(int) * 2);
		if (!fd[0][i])
			ft_error();
		err = pipe(fd[0][i]);
		if (err == -1)
			ft_error();
	}
	pid[0] = malloc(sizeof(int) * cmd_cnt);
	if (!pid[0])
		ft_error();
}

static void		first_pipe(int ***fd, t_pipe p, t_v *v, t_ls *data)
{
	p.pid[0] = fork();
	if (p.pid[0] == -1)
		ft_error();
	if (p.pid[0] == 0)
	{
		dup2(fd[0][0][1], 1);
		if (fd[0][0][1] == -1)
			ft_error();
		close_fd(fd[0], p.cmd_cnt);
		infinity_loop(&v, data->words1[0], data);
		free_tab(&data->words1);
		free_fd(fd, p.cmd_cnt);
		free(p.pid);
		exit (1);
	}	
}

static void	mid_pipes(int ***fd, t_pipe p, t_v *v, t_ls *data)
{
	int	i;
	
	i = 0;
	while (++i < p.cmd_cnt - 1)
	{	
		p.pid[i] = fork();
		if (p.pid[i] == -1)
			ft_error();
		if (p.pid[i] == 0)
		{
			dup2(fd[0][i - 1][0], 0);
			if (fd[0][i - 1][0] == -1)
				ft_error();
			dup2(fd[0][i][1], 1);
			if (fd[0][i][1] == -1)
				ft_error();
			close_fd(fd[0], p.cmd_cnt);
			infinity_loop(&v, data->words1[i], data);
			free_tab(&data->words1);
			free_fd(fd, p.cmd_cnt);
			free(p.pid);
			exit (1);
		}
	}	
}

static void	last_pipe(int ***fd, t_pipe p, t_v *v, t_ls *data)
{
	int	i;
	
	i = p.cmd_cnt - 1;
	p.pid[i] = fork();
	if (p.pid[i] == -1)
		ft_error();
	if (p.pid[i] == 0)
	{
		dup2(fd[0][i - 1][0], 0);
		if (fd[0][i - 1][0] == -1)
			ft_error();
		close_fd(fd[0], p.cmd_cnt);
		infinity_loop(&v, data->words1[i], data);
		free_tab(&data->words1);
		free_fd(fd, p.cmd_cnt);
		free(p.pid);
		exit (1);
	}
}

int	ft_pipe(t_v *v, char **line, t_ls *data)
{
	int			i;
	int			**fd;
	t_pipe		p;

	data->words1 = shell_split(line[0], '|');
	if (!data->words1)
		ft_error();
	p.cmd_cnt = tab_cnt(data->words1);
	if (p.cmd_cnt == 1)
	{
		free_tab(&data->words1);
		return (0);
	}
	pipes_and_pids(&fd, &p.pid, p.cmd_cnt);
	first_pipe(&fd, p, v, data);
	mid_pipes(&fd, p, v, data);
	last_pipe(&fd, p, v, data);
	close_fd(fd, p.cmd_cnt);
	free_tab(&data->words1);
	free_fd(&fd, p.cmd_cnt);
	i = -1;
	while (++i < p.cmd_cnt)
		wait(&p.pid[i]);
	free(p.pid);
	return (1);
}
