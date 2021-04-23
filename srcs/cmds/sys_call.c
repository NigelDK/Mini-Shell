/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:22:33 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/23 19:04:31 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*path_variable(t_ls *data, int *j, t_v **v)
{
	struct stat	info;
	char		**path;
	char		*temp;
	char		*cmd;

	data->i = -1;
	temp = ft_strjoin("/", data->words2[0]);
	path = shell_split(getenv("PATH"), ':');
	while (path[++data->i])
	{
		cmd = ft_strjoin2(path[data->i], temp);
		if (!cmd)
			ft_error_syscall(data, v, path, temp);
		if (lstat(cmd, &info) == 0)
		{
			*j = 1;
			break ;
		}
		free(cmd);
	}
	free(path);
	if (*j == 0)
		return (temp);
	free(temp);
	return (cmd);
}

void	child_call(t_ls *data, t_v **v, char *cmd, int j)
{
	if (execve(cmd, data->words2, data->envp) < 0)
		printf("zsh: command not found: %s\n", data->words2[0]);
	if (j == 1)
		free(cmd);
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
