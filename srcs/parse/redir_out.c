/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:55:22 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/27 21:45:54 by nde-koni         ###   ########.fr       */
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
	(redir_out_at_start(line)) ? (j = 0) : (j = 1);
	(redir_out_at_start(line)) ? (cmd_cnt++) : (0);
	k = 0;
	if (!(fd = malloc(sizeof(int) * (cmd_cnt - 1))))
		ft_error();
	while (++i < cmd_cnt - 1)
	{
		if (!(filename = shell_split(data->words3[j++], ' ')))
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
	if (!(data->words3 = shell_split(line, '>')))
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

/*
void	check_append(char *line, int *append)
{
	int	i;
	int	j;
	int	q;
	int	dq;

	i = -1;
	j = 0;
	q = 0;
	dq = 0;
	while (line[++i])
	{
		if (line[i] == 39)
			(q == 0 && dq == 0) ? (q = 1) : (q = 0);
		if (line[i] == '"')
			(dq == 0 && q == 0) ? (dq = 1) : (dq = 0);
		(line[i - 1] != '>' && line[i] == '>' && line[i + 1] != '>'
			&& q == 0 && dq == 0) ? (append[0] = 0) : (0);
		(line[i] == '>' && line[i + 1] == '>' && q == 0 && dq == 0) ?
			(append[0] = 1) : (0);
		(line[i] == '>' && line[i + 1] == '>' && line[i + 2]
		&& line[i + 2] == '>' && q == 0 && dq == 0) ? (ft_error()) : (0);
		(line[i] == '>') ? (j++) : (0);
		(j > 2) ? (ft_error()) : (0);
	}
}

int	redir_out(t_v **v, char *line, t_ls *data)
{
	int		cmd_cnt;
	int		pid;
	int		fd;
	int		append;
	char	**filename;
	
	if (!(data->words3 = shell_split(line, '>')))
		ft_error();
	if ((cmd_cnt = tab_cnt(data->words3)) == 1)
	{
		free_tab(&data->words3);
		return (0);
	}
	if ((cmd_cnt = tab_cnt(data->words3)) > 2)
		ft_error();
	check_append(line, &append);
	if ((pid = fork()) == -1)
		ft_error();
	if (pid == 0)
	{
		if (!(filename = shell_split(data->words3[1], ' ')))
			ft_error();
		if (!append)
			if ((fd = open(filename[0], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
				ft_error();
		if (append)
			if ((fd = open(filename[0], O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
				ft_error();
		if (dup2(fd, 1) == -1)
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