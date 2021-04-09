/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:55:22 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/09 20:35:26 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		free_tab(&data->words3);
		free_tab(&filename);
		exit (1);
	}
	free_tab(&data->words3);
	wait(&pid);
	return (1);
}
