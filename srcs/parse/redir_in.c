/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 20:19:57 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/29 10:19:13 by nde-koni         ###   ########.fr       */
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
		if (i == 0)
			s++;
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

static void	open_close_fd(int *fd, int i, char **filename)
{
	fd[i] = open(filename[0], O_RDONLY, 0644);
	if (fd[i] == -1)
	{
		printf("bash: %s: No such file or directory\n", filename[0]);
		free_tab(&filename);
		exit (1);
	}
	dup2(fd[i], 0);
	if (fd[i] == -1)
		ft_error();
	close(fd[i]);
	free_tab(&filename);
}

static void	child_process(t_v **v, char *line, t_ls *data, int cmd_cnt)
{
	int		i;
	int		j;
	int		*fd;
	char	**filename;

	i = -1;
	j = 1;
	if (redir_at_start(line))
	{
		j = 0;
		cmd_cnt++;
	}
	fd = malloc(sizeof(int) * (cmd_cnt - 1));
	if (!fd)
		ft_error();
	while (++i < cmd_cnt - 1)
	{
		filename = shell_split(data->words3[j++], ' ');
		if (!filename)
			ft_error();
		open_close_fd(fd, i, filename);
	}
	if (!redir_at_start(line))
		infinity_loop(v, data->words3[0], data);
	exit (0);
}

int	redir_in(t_v **v, char *line, t_ls *data)
{
	int		cmd_cnt;
	int		pid;

	if (too_many_redir(line))
		exit (2);
	data->words3 = shell_split(line, '<');
	if (!data->words3)
		ft_error();
	cmd_cnt = tab_cnt(data->words3);
	if (cmd_cnt == 1 && !redir_at_start(line))
	{
		free_tab(&data->words3);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid == 0)
		child_process(v, line, data, cmd_cnt);
	free_tab(&data->words3);
	wait(&pid);
	return (1);
}
