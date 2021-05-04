/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 21:11:02 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/04 12:26:46 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_fd(int ***fd, int cmd_cnt)
{
	int	i;

	i = -1;
	while (++i < cmd_cnt - 1)
		free_int(&fd[0][i]);
	free(fd[0]);
	fd[0] = NULL;
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
