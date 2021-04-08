/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:49:09 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/07 18:03:40 by nde-koni         ###   ########.fr       */
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

int			ft_pipe(t_v *v, char *line, t_ls *data)
{
	int		i;
	int		j;
	int		cmd_cnt;
	int		*pid;
	char	**cmds;
	int		**fd;
	
	if (!(cmds = shell_split(line, '|')))
		ft_error();
	cmd_cnt = tab_cnt(cmds);
	if (cmd_cnt == 1)
		return (0);

	// malloc and open pipes
	if (!(fd = malloc(sizeof(int *) * (cmd_cnt - 1))))
		ft_error();
	i = -1;
	while (++i < cmd_cnt - 1)
	{
		if (!(fd[i] = malloc(sizeof(int) * 2)))
			ft_error();
		if (pipe(fd[i]) == -1)
			ft_error();
	}
	if (!(pid = malloc(sizeof(int) * cmd_cnt)))
		ft_error();

	// first pipe
	if ((pid[0] = fork()) == -1)
		ft_error();
	if (pid[0] == 0)
	{
		if (dup2(fd[0][1], 1) == -1)
			ft_error();
		j = -1;
		while (++j < cmd_cnt - 1)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		infinity_loop(&v, cmds[0], data);
		exit (1);
	}

	// mid body pipes
	i = 0;
	while (++i < cmd_cnt - 1)
	{	
		if ((pid[i] = fork()) == -1)
			ft_error();
		if (pid[i] == 0)
		{
			if (dup2(fd[i - 1][0], 0) == -1)
				ft_error();
			if (dup2(fd[i][1], 1) == -1)
				ft_error();
			j = -1;
			while (++j < cmd_cnt - 1)
			{
				close(fd[j][0]);
				close(fd[j][1]);
			}
			infinity_loop(&v, cmds[i], data);
			exit (1);
		}
	}

	// last pipe
	i = cmd_cnt - 1;
	if ((pid[i] = fork()) == -1)
		ft_error();
	if (pid[i] == 0)
	{
		if (dup2(fd[i - 1][0], 0) == -1)
			ft_error();
		j = -1;
		while (++j < cmd_cnt - 1)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		infinity_loop(&v, cmds[i], data);
		exit (1);
	}
	i = -1;
	while (++i < cmd_cnt - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	i = -1;
	while (++i < cmd_cnt)
		wait(&pid[i]);
	return (1);
}
/*
int			ft_pipe(t_v *v, char *line, int *cd, t_ls data)
{
	int		i;
	int		fd[2][2];
	int		pid[3];
	int		cmd_cnt;
	char	**cmds;

	i = -1;
	if (!(cmds = shell_split(line, '|')))
		ft_error_split(&line, &cmds);
	cmd_cnt = tab_cnt(cmds);
	if (cmd_cnt == 1)
	{
		free(cmds[0]);
		free(cmds);
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
			infinity_loop(&v, cmds[0], cd, data);
			while (cmds[++i])
				free(cmds[i]);
			free(cmds);
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
			infinity_loop(&v, cmds[1], cd, data);
			while (cmds[++i])
				free(cmds[i]);
			free(cmds);
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
			infinity_loop(&v, cmds[2], cd, data);
			while (cmds[++i])
				free(cmds[i]);
			free(cmds);
			exit (1);
		}
	}
	while (cmds[++i])
		free(cmds[i]);
	free(cmds);
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
	wait(&pid[0]);
	wait(&pid[1]);
	wait(&pid[2]);
	return (1);
}*/
