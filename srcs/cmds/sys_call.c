/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:22:33 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/05 13:24:26 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_lstat(char *cmd, int *j, int a)
{
	struct stat	info;

	if (lstat(cmd, &info) == 0)
	{
		if (a == 1)
			*j = 1;
		else
			*j = 24223;
		return (0);
	}
	else
		return (1);
}

char	*path_variable(t_ls *data, int *j, t_v **v)
{
//	if (get_lstat(data->words2[0], j, 0) == 0)
//		return (data->words2[0]);
	data->i = -1;
	data->sys.temp = ft_strjoin("/", data->words2[0]);
	if (!data->sys.temp)
		ft_error(data, v);
	data->sys.path = shell_split(getenv("PATH"), ':');
	if (!data->sys.path)
		ft_error(data, v);
	while (data->sys.path[++data->i])
	{
		data->sys.cmd = ft_strjoin(data->sys.path[data->i], data->sys.temp);
		if (!data->sys.cmd)
			ft_error(data, v);
		if (get_lstat(data->sys.cmd, j, 1) == 0)
			break ;
		free(data->sys.cmd);
	}
	data->i = -1;
	while (data->sys.path[++data->i])
		free_string(&data->sys.path[data->i]);
	free_2d_string(&data->sys.path);
	free_string(&data->sys.temp);
	return (data->sys.cmd);
}

void	child_call(t_ls *data, t_v **v, char *cmd, int j)
{
	if (execve(cmd, data->words2, data->envp) < 0)
		if (data->words2[0])
			ft_printf_fd(2,
				"minishell: %s: command not found\n", data->words2[0]);
	if (j == 1)
		free(cmd);
	if (!data->words2[0])
		exit(data->statuscode);
	ft_free_all(data, v);
	exit(127);
}

void	sys_call(t_ls *data, t_v **v)
{
	pid_t	pid;
	char	*cmd;
	int		j;
	int		wstatus;

	j = 0;
	cmd = path_variable(data, &j, v);
	pid = fork();
	if (pid < 0)
	{
		free(cmd);
		ft_error(data, v);
	}
	if (pid == 0)
		child_call(data, v, cmd, j);
	if (j == 1)
		free(cmd);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		data->statuscode = WEXITSTATUS(wstatus);
}
