/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:49:09 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/04 11:38:50 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	pipes_and_pids(t_ls *data, t_v *v)
{
	int	i;

	data->p.fd = malloc(sizeof(int *) * (data->p.cmd_cnt - 1));
	if (!data->p.fd)
		ft_error(data, &v);
	i = -1;
	while (++i < data->p.cmd_cnt - 1)
	{
		data->p.fd[i] = malloc(sizeof(int) * 2);
		if (!data->p.fd[i])
			ft_error(data, &v);
		if (pipe(data->p.fd[i]) == -1)
			ft_error(data, &v);
	}
	data->p.pid = malloc(sizeof(int) * data->p.cmd_cnt);
	if (!data->p.pid)
		ft_error(data, &v);
}

static void	first_pipe(t_v *v, t_ls *data)
{
	data->p.pid[0] = fork();
	if (data->p.pid[0] == -1)
		ft_error();
	if (data->p.pid[0] == 0)
	{
		if (dup2(data->p.fd[0][1], 1) == -1)
			ft_error(data, &v);
		close_fd(data->p.fd, data->p.cmd_cnt);
		infinity_loop(&v, data->words1[0], data);
		free_tab(&data->words1);
		free_fd(&data->p.fd, data->p.cmd_cnt);
		free_int(&data->p.pid);
		exit (1);
	}	
}

static void	mid_pipes(t_v *v, t_ls *data)
{
	int	i;

	i = 0;
	while (++i < data->p.cmd_cnt - 1)
	{	
		data->p.pid[i] = fork();
		if (data->p.pid[i] == -1)
			ft_error(data, &v);
		if (data->p.pid[i] == 0)
		{
			if (dup2(data->p.fd[i - 1][0], 0) == -1)
				ft_error();
			if (dup2(data->p.fd[i][1], 1) == -1)
				ft_error(data, &v);
			close_fd(data->p.fd, data->p.cmd_cnt);
			infinity_loop(&v, data->words1[i], data);
			free_tab(&data->words1);
			free_fd(&data->p.fd, data->p.cmd_cnt);
			free_int(&data->p.pid);
			exit (1);
		}
	}	
}

static void	last_pipe(t_v *v, t_ls *data)
{
	int	i;

	i = data->p.cmd_cnt - 1;
	data->p.pid[i] = fork();
	if (data->p.pid[i] == -1)
		ft_error(data, &v);
	if (data->p.pid[i] == 0)
	{
		if (dup2(data->p.fd[i - 1][0], 0) == -1)
			ft_error(data, &v);
		close_fd(data->p.fd, data->p.cmd_cnt);
		infinity_loop(&v, data->words1[i], data);
		free_tab(&data->words1);
		free_fd(&data->p.fd, data->p.cmd_cnt);
		free_int(&data->p.pid);
		exit (1);
	}
}

int	ft_pipe(t_v *v, char **line, t_ls *data)
{
	data->words1 = shell_split(line[0], '|');
	if (!data->words1)
		ft_error(data, &v);
	data->p.cmd_cnt = tab_cnt(data->words1);
	if (data->p.cmd_cnt == 1)
	{
		free_tab(&data->words1);
		return (0);
	}
	pipes_and_pids(data, v);
	first_pipe(v, data);
	wait(&data->p.pid[0]);
	mid_pipes(v, data);
	last_pipe(v, data);
	close_fd(data->p.fd, data->p.cmd_cnt);
	free_tab(&data->words1);
	free_fd(&data->p.fd, data->p.cmd_cnt);
	data->p.i = 0;
	while (++data->p.i < data->p.cmd_cnt)
		wait(&data->p.pid[data->p.i]);
	free_int(&data->p.pid);
	return (1);
}
