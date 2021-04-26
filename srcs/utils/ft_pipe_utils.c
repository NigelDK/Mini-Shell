/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 21:11:02 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/26 19:08:15 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_fd(int ***fd, int cmd_cnt)
{
	int	i;

	i = -1;
	while (++i < cmd_cnt - 1)
		free(fd[0][i]);
	free(fd[0]);
}

void	close_fd(int **fd, int cmd_cnt)
{
	int	i;

	i = -1;
	while (++i < cmd_cnt - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}
/*
void	double_pipe_trim(char **s)
{
	int	i;

	i = 0;
	while (s[0][i])
	{
		if (s[0][i] ==
	}
}
*/