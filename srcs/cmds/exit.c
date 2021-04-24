/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin </var/mail/minummin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:33:17 by minummin          #+#    #+#             */
/*   Updated: 2021/04/23 19:11:38 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strisnum(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (ft_isdigit(s[i]) == 0)
			return (0);
	return (1);
}

void	ft_exit_2(char **words, int i)
{
	int	tmp;

	if (words[1] && !words[2])
	{
		tmp = ft_atoi(words[1]);
		if (tmp > 255)
			tmp = tmp % 256;
		printf("exit\n");
		while (words[++i])
			free(words[i]);
		free(words);
		exit(tmp);
	}
	else
	{
		printf("exit\n");
		while (words[++i])
			free(words[i]);
		free(words);
		exit(0);
	}
}

void	ft_exit(char **words, t_v **v, char *temp, t_ls *data)
{
	int	i;

	if (words[1] && words[2] && ft_strisnum(words[1]) == 1)
	{
		data->statuscode = 500;
		printf("exit\nexit: too many arguments\n");
		return ;
	}
	i = -1;
	free(temp);
	ft_lstclear_2(v, ft_memdel);
	if (words[1] && ft_strisnum(words[1]) == 0)
	{
		printf("exit\nexit: %s: numeric argument required\n", words[1]);
		while (words[++i])
			free(words[i]);
		free(words);
		exit(128);
	}
	ft_exit_2(words, i);
}
