/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:19:57 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/09 20:41:33 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		free_tab(&data->words3);
		free_tab(&filename);
		exit (1);
	}
	free_tab(&data->words3);
	wait(&pid);
	return (1);
}
