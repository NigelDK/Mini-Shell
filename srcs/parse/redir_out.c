/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:55:22 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/28 18:03:16 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	trim_filename(char **filename)
{
	char	*tmp;

	tmp = d_dq_trim_pad_str(filename[0]);
	free(filename[0]);
	filename[0] = tmp;
	tmp = bslash_trim_str(filename[0]);
	free(filename[0]);
	filename[0] = tmp;
}

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

static void	open_close_fd(int *fd, int i, char **filename, int j)
{
	trim_filename(filename);
	if (j)
		fd[i] = open(filename[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd[i] = open(filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[i] == -1)
	{
		printf("bash: %s: No such file or directory\n", filename[0]);
		free_tab(&filename);
		exit (1);
	}
	if (dup2(fd[i], 1) == -1)
		ft_error();
	close(fd[i]);
	free_tab(&filename);
}

static void	child_process(t_v **v, char *line, t_ls *data, int cmd_cnt)
{
	int		i;
	int		j;
	int		k;
	int		*fd;
	char	**filename;

	i = -1;
	if (redir_out_at_start(line))
	{
		j = 0;
		cmd_cnt++;
	}
	else
		(j = 1);
	k = 0;
	fd = malloc(sizeof(int) * (cmd_cnt - 1));
	if (!fd)
		ft_error();
	while (++i < cmd_cnt - 1)
	{
		filename = shell_split(data->words3[j++], ' ');
		if (!filename)
			ft_error();
		if (!append(line, &k))
			open_close_fd(fd, i, filename, 0);
		else
			open_close_fd(fd, i, filename, 1);
	}
	redir_trim(data, line);
	infinity_loop(v, data->words3[0], data);
	exit (0);
}

int			redir_out(t_v **v, char *line, t_ls *data)
{
	int		cmd_cnt;
	int		pid;
	
	if (too_many_redir_out(line))
		exit (2);
	data->words3 = shell_split(line, '>');
	if (!data->words3)
		ft_error();
	cmd_cnt = tab_cnt(data->words3);
	if (cmd_cnt == 1 && !redir_out_at_start(line))
	{
		free_tab(&data->words3);
		return (0);
	}
	if ((pid = fork()) == -1)
		ft_error();
	if (pid == 0)
		child_process(v, line, data, cmd_cnt);
	free_tab(&data->words3);
	wait(&pid);
	return (1);
}
