/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:19:57 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/11 18:14:43 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	open_close_fd(t_ls *data, t_v **v, int i)
{
	data->ri.fd[i] = open(data->ri.filename[0], O_RDONLY, 0644);
	if (data->ri.fd[i] == -1)
	{
		ft_printf_fd(2,
			"minishell: %s: No such file or directory\n", data->ri.filename[0]);
		free_tab(&data->ri.filename);
		exit (1);
	}
	if (dup2(data->ri.fd[i], 0) == -1)
		ft_error(data, v);
	close(data->ri.fd[i]);
	free_tab(&data->ri.filename);
}

static void	child_process(t_v **v, char *line, t_ls *data, int cmd_cnt)
{
	int		i;
	int		j;

	i = -1;
	j = 1;
	if (redir_at_start(line))
	{
		j = 0;
		cmd_cnt++;
	}
	data->ri.fd = malloc(sizeof(int) * (cmd_cnt - 1));
	if (!data->ri.fd)
		ft_error(data, v);
	while (++i < cmd_cnt - 1)
	{
		data->ri.filename = shell_split(data->words3[j++], ' ');
		if (!data->ri.filename[0])
			ft_error(data, v);
		open_close_fd(data, v, i);
	}
	if (!redir_at_start(line))
		infinity_loop(v, data->words3[0], data);
	exit (0);
}

int	redir_in(t_v **v, char *line, t_ls *data)
{
	int		cmd_cnt;
	int		pid;

	if (too_many_redir_in(line))
		exit (2);
	data->words3 = shell_split(line, '<');
	if (!data->words3)
		ft_error(data, v);
	cmd_cnt = tab_cnt(data->words3);
	if (cmd_cnt == 1 && !redir_at_start(line))
	{
		free_tab(&data->words3);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		ft_error(data, v);
	if (pid == 0)
		child_process(v, line, data, cmd_cnt);
	free_tab(&data->words3);
	wait(&pid);
	return (1);
}
