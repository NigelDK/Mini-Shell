/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:22:33 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/12 13:53:47 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*path_variable(t_ls *data, int *j, t_v **v)
{
	struct stat info;
	char **path;
	char *temp;
	char *cmd;
	int i;

	i = -1;
	temp = ft_strjoin("/", data->words2[0]);
	path = shell_split(getenv("PATH"), ':');
	while (path[++i])
	{
		if (!(cmd = ft_strjoin2(path[i], temp)))
		{
			ft_putstr("haha");
			ft_error_syscall(data, v, path, temp);
		}
		if (lstat(cmd, &info) == 0)
		{
			*j = 1;
			break;
		}
		free(cmd);
	}
	free(temp);
	/*	i = -1;
		while (path[++i])
		free(path[i]);*/
	free(path);
	return (cmd);
}

void	sys_call(t_ls *data, t_v **v)
{
	pid_t	pid;
	char	*cmd;
	int j;
	char	*temp;

	j = 0;
	cmd = path_variable(data, &j, v);
	if ((pid = fork()) < 0)
	{
		free(cmd);
		ft_error_data_v_2(data, v);
	}
	if (pid == 0)
	{
		if (execve(cmd, data->words2, data->envp) < 0)
		{
			if (data->words[0][0] == '$')
			{
				while ((*v)->next)
				{
					temp = ft_strstr_reverse((*v)->str, "=");
					if (ft_strcmp_2(data->words2[0], temp, 0) == 0)
						printf("%s: %s\n", ft_strstr_2((*v)->str, "="), strerror(errno));
					free(temp);
					*v = (*v)->next;
				}
			}
			else
				printf("zsh: command not found: %s\n", data->words2[0]);
		}
		if (j == 1)
			free(cmd);
		ft_error_data_v_child(data, v);
		exit (1);
	}
	if (j == 1)
		free(cmd);
	wait(&pid);
}
