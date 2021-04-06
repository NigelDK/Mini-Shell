/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:22:33 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/05 16:18:31 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*path_variable(char **words, int *j)
{
	struct stat info;
	char **path;
	char *temp;
	char *cmd;
	int i;

	i = -1;
	temp = ft_strjoin("/", words[0]);
	path = shell_split(getenv("PATH"), ':');
	while (path[++i])
	{
		if (!(cmd = ft_strjoin(path[i], temp)))
			ft_error();
		if (lstat(cmd, &info) == 0)
		{
			*j = 1;
			break;
		}
		free(cmd);
	}
	free(temp);
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	return (cmd);
}

void	sys_call(char **words, t_ls data)
{
	pid_t	pid;
	char	*cmd;
	int j;

	j = 0;
	cmd = path_variable(words, &j);
	if ((pid = fork()) < 0)
		ft_error();
	if (pid == 0)
	{
		if (execve(cmd, words, data.envp) < 0)
			printf("zsh: command not found: %s\n", words[0]);
		if (j == 1)
			free(cmd);
		exit (1);
	}
	if (j == 1)
		free(cmd);
	wait(&pid);
}
