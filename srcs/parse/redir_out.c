/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:55:22 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/04 11:41:54 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append(char *s, int *k)
{
	int	i;

	i = 0;
	while (s[*k] && s[*k] != '>')
		k[0]++;
	while (s[*k] && s[*k] == '>')
	{
		i++;
		k[0]++;
	}
	if (i == 2)
		return (1);
	return (0);
}

static void	open_close_fd(t_ls *data, t_v **v, int i, int j)
{
	trim_filename(data);
	if (j)
		data->ro.fd[i] = open(data->ro.filename[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->ro.fd[i] = open(data->ro.filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->ro.fd[i] == -1)
	{
		ft_printf_fd(2,
			"minishell: %s: No such file or directory\n", data->ro.filename[0]);
		ft_error(data, v);
		exit (1);
	}
	if (dup2(data->ro.fd[i], 1) == -1)
		ft_error(data, v);
	close(data->ro.fd[i]);
	free_tab(&data->ro.filename);
}

static void	init_val(int *i, char *line, int *j, int *cmd_cnt)
{
	i[0] = -1;
	if (redir_out_at_start(line))
	{
		j[0] = 0;
		cmd_cnt[0]++;
	}
	else
		(j[0] = 1);
}

static void	child_process(t_v **v, char *line, t_ls *data, int cmd_cnt)
{
	int		i;
	int		j;
	int		k;

	init_val(&i, line, &j, &cmd_cnt);
	k = 0;
	data->ro.fd = malloc(sizeof(int) * (cmd_cnt - 1));
	if (!data->ro.fd)
		ft_error(data, v);
	while (++i < cmd_cnt - 1)
	{
		data->ro.filename = shell_split(data->words3[j++], ' ');
		if (!data->ro.filename)
			ft_error(data, v);
		if (!append(line, &k))
			open_close_fd(data, v, i, 0);
		else
			open_close_fd(data, v, i, 1);
	}
	redir_trim(data, v, line);
	infinity_loop(v, data->words3[0], data);
	exit (0);
}

int	redir_out(t_v **v, char *line, t_ls *data)
{
	int		cmd_cnt;
	int		pid;

	if (too_many_redir_out(line))
		return (1);
	data->words3 = shell_split(line, '>');
	if (!data->words3)
		ft_error(data, v);
	cmd_cnt = tab_cnt(data->words3);
	if (cmd_cnt == 1 && !redir_out_at_start(line))
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
