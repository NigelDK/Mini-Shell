/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:19:57 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/21 17:38:17 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	too_many_redir(char *s)
{
	int	i;
	
	while (*s)
	{
		i = 0;
		while (*s == '<')
		{
			i++;
			s++;
		}
		if (i > 1)
		{
			printf("bash:  syntax error near unexpected token `");
			while (i-- > 1)
				printf("<");
			printf("'\n");
			return (1);
		}
		(i == 0) ? (s++) : (0);
	}
	return (0);
}

static int	redir_at_start(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '<')
		return (1);
	return (0);
}

int			redir_in(t_v **v, char *line, t_ls *data)
{
	int		i;
	int		j;
	int		cmd_cnt;
	int		pid;
	int		*fd;
	char	**filename;
	
	if (too_many_redir(line))
		return (1); // I need to have exit status here
	if (!(data->words3 = shell_split(line, '<')))
		ft_error();
	cmd_cnt = tab_cnt(data->words3);
	if (cmd_cnt == 1 && !redir_at_start(line))
	{
		free_tab(&data->words3);
		return (0);
	}
	if ((pid = fork()) == -1)
		ft_error();
	if (pid == 0)
	{
		i = 0;
		(redir_at_start(line)) ? (j = 0) : (j = 1);
		(redir_at_start(line)) ? (cmd_cnt++) : (0);
		if (!(fd = malloc(sizeof(int) * (cmd_cnt - 1))))
			ft_error();
		while (i < cmd_cnt - 1)
		{
			if (!(filename = shell_split(data->words3[j], ' ')))
				ft_error();
			if ((fd[i] = open(filename[0], O_RDONLY, 0644)) == -1)
			{
				printf("bash: %s: No such file or directory\n", filename[0]);
				free_tab(&filename);
				return (1);
			}
			if (dup2(fd[i], 0) == -1)
				ft_error();
			close(fd[i]);
			free_tab(&filename);
			i++;
		}
		if (!redir_at_start(line))
			infinity_loop(v, data->words3[0], data);
		exit (1);
	}
	free_tab(&data->words3);
	wait(&pid);
	return (1);
}

/*
int	redir_in(t_v **v, char *line, t_ls *data)
{
	int		cmd_cnt;
	int		pid;
	int		fd;
	char	**filename;
	
	if (!(data->words3 = shell_split(line, '<')))
		ft_error();
	if ((cmd_cnt = tab_cnt(data->words3)) == 1)
	{
		free_tab(&data->words3);
		return (0);
	}
	if ((cmd_cnt = tab_cnt(data->words3)) > 2)
		ft_error();
	if ((pid = fork()) == -1)
		ft_error();
	if (pid == 0)
	{
		if (!(filename = shell_split(data->words3[1], ' ')))
			ft_error();
		if ((fd = open(filename[0], O_RDONLY, 0644)) == -1)
			ft_error();
		if (dup2(fd, 0) == -1)
			ft_error();
		close(fd);
		infinity_loop(v, data->words3[0], data);
//		free_tab(&data->words3);
		free_tab(&filename);
		exit (1);
	}
	free_tab(&data->words3);
	wait(&pid);
	return (1);
}
*/