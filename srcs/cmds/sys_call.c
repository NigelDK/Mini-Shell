/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:22:33 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/30 10:49:30 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_lstat(char *cmd, int *j)
{
	struct stat	info;

	if (lstat(cmd, &info) == 0)
	{
		*j = 1;
		return (0);
	}
	else
		return (1);
}

char	*path_variable(t_ls *data, int *j, t_v **v)
{
	char		**path;
	char		*temp;
	char		*cmd;

	data->i = -1;
	temp = ft_strjoin("/", data->words2[0]);
	path = shell_split(getenv("PATH"), ':');
	while (path[++data->i])
	{
		cmd = ft_strjoin(path[data->i], temp);
		if (!cmd)
			ft_error_syscall(data, v, path, temp);
		if (get_lstat(cmd, j) == 0)
			break ;
		free(cmd);
	}
	data->i = -1;
	while (path[++data->i])
		free(path[data->i]);
	free(path);
	free(temp);
	return (cmd);
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
	ft_error_data_v_child(data, v);
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
		ft_error_data_v_2(data, v);
	}
	if (pid == 0)
		child_call(data, v, cmd, j);
	if (j == 1)
		free(cmd);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		data->statuscode = WEXITSTATUS(wstatus);
}
