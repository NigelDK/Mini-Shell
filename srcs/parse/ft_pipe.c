/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:49:09 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/09 10:50:26 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		pipes_and_pids(int ***fd, int **pid, int cmd_cnt)
{
	int	i;

	if (!(fd[0] = malloc(sizeof(int *) * (cmd_cnt - 1))))
		ft_error();
	i = -1;
	while (++i < cmd_cnt - 1)
	{
		if (!(fd[0][i] = malloc(sizeof(int) * 2)))
			ft_error();
		if (pipe(fd[0][i]) == -1)
			ft_error();
	}
	if (!(pid[0] = malloc(sizeof(int) * cmd_cnt)))
		ft_error();
}

static void		first_pipe(int ***fd, t_pipe p, t_v *v, t_ls *data)
{
	if ((p.pid[0] = fork()) == -1)
		ft_error();
	if (p.pid[0] == 0)
	{
		if (dup2(fd[0][0][1], 1) == -1)
			ft_error();
		close_fd(fd[0], p.cmd_cnt);
		infinity_loop(&v, data->words1[0], data);
		free_tab(&data->words1);
		free_fd(fd, p.cmd_cnt);
		free(p.pid);
		exit (1);
	}	
}

static void		mid_pipes(int ***fd, t_pipe p, t_v *v, t_ls *data)
{
	int	i;
	
	i = 0;
	while (++i < p.cmd_cnt - 1)
	{	
		if ((p.pid[i] = fork()) == -1)
			ft_error();
		if (p.pid[i] == 0)
		{
			if (dup2(fd[0][i - 1][0], 0) == -1)
				ft_error();
			if (dup2(fd[0][i][1], 1) == -1)
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

static void		last_pipe(int ***fd, t_pipe p, t_v *v, t_ls *data)
{
	int	i;
	
	i = p.cmd_cnt - 1;
	if ((p.pid[i] = fork()) == -1)
		ft_error();
	if (p.pid[i] == 0)
	{
		if (dup2(fd[0][i - 1][0], 0) == -1)
			ft_error();
		close_fd(fd[0], p.cmd_cnt);
		infinity_loop(&v, data->words1[i], data);
		free_tab(&data->words1);
		free_fd(fd, p.cmd_cnt);
		free(p.pid);
		exit (1);
	}
}

int				ft_pipe(t_v *v, char *line, t_ls *data)
{
	int			i;
	int			**fd;
	t_pipe		p;
	
	if (!(data->words1 = shell_split(line, '|')))
		ft_error();
	if ((p.cmd_cnt = tab_cnt(data->words1)) == 1)
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


/*
int			ft_pipe(t_v *v, char *line, int *cd, t_ls data)
{
	int		i;
	int		fd[2][2];
	int		pid[3];
	int		cmd_cnt;
	char	**data->words1;

	i = -1;
	if (!(data->words1 = shell_split(line, '|')))
		ft_error_split(&line, &data->words1);
	cmd_cnt = tab_cnt(data->words1);
	if (cmd_cnt == 1)
	{
		free(data->words1[0]);
		free(data->words1);
		return (0);
	}
	else
	{
		if (pipe(fd[0]) == -1)
			ft_error();
		if (pipe(fd[1]) == -1)
			ft_error();
		if ((pid[0] = fork()) < 0)
			ft_error();
		if (pid[0] == 0)
		{
			if (dup2(fd[0][1], 1) == -1)
				ft_error();
			close(fd[0][0]);
			close(fd[0][1]);
			close(fd[1][0]);
			close(fd[1][1]);
			infinity_loop(&v, data->words1[0], cd, data);
			while (data->words1[++i])
				free(data->words1[i]);
			free(data->words1);
			exit (1);
		}
//
		if ((pid[1] = fork()) < 0)
			ft_error();
		if (pid[1] == 0)
		{
			if (dup2(fd[0][0], 0) == -1)
				ft_error();
			if (dup2(fd[1][1], 1) == -1)
				ft_error();
			close(fd[0][0]);
			close(fd[0][1]);
			close(fd[1][0]);
			close(fd[1][1]);
			infinity_loop(&v, data->words1[1], cd, data);
			while (data->words1[++i])
				free(data->words1[i]);
			free(data->words1);
			exit (1);
		}
//
		if ((pid[2] = fork()) < 0)
			ft_error();
		if (pid[2] == 0)
		{
			if (dup2(fd[1][0], 0) == -1)
				ft_error();
			close(fd[0][0]);
			close(fd[0][1]);
			close(fd[1][0]);
			close(fd[1][1]);
			infinity_loop(&v, data->words1[2], cd, data);
			while (data->words1[++i])
				free(data->words1[i]);
			free(data->words1);
			exit (1);
		}
	}
	while (data->words1[++i])
		free(data->words1[i]);
	free(data->words1);
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
	wait(&pid[0]);
	wait(&pid[1]);
	wait(&pid[2]);
	return (1);
}*/
