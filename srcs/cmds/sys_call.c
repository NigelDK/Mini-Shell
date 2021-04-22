/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:22:33 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/22 22:01:14 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*path_variable(t_ls *data, int *j, t_v **v)
{
	struct stat	info;
	char		**path;
	char		*temp;
	char		*cmd;
	int			i;

	i = -1;
	temp = ft_strjoin("/", data->words2[0]);
	path = shell_split(getenv("PATH"), ':');
	while (path[++i])
	{
		cmd = ft_strjoin2(path[i], temp);
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

void	child_call_exit(t_ls *data, t_v **v, char *cmd, int j)
{
	if (j == 1)
		free(cmd);
	ft_error_data_v_child(data, v);
	exit(127);
}

void	child_call(t_ls *data, t_v **v, char *cmd, int j)
{
	char	*temp;

	if (execve(cmd, data->words2, data->envp) < 0)
	{
		if (data->words2[0][0] == '$')
		{
			if (data->words2[0][1]
					== '?' && ft_isalpha(data->words2[0][2]) == 0)
				printf("%s: %d\n", strerror(errno), data->statuscode);
			while ((*v)->next)
			{
				temp = ft_strstr_reverse((*v)->str, "=");
				if (ft_strcmp_2(data->words2[0], temp, 0) == 0)
					printf("%s: %s\n",
						ft_strstr_2((*v)->str, "="), strerror(errno));
				free(temp);
				*v = (*v)->next;
			}
		}
		else
			printf("zsh: command not found: %s\n", data->words2[0]);
	}
	child_call_exit(data, v, cmd, j);
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
