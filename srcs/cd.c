/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin </var/mail/minummin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:35:38 by minummin          #+#    #+#             */
/*   Updated: 2021/04/03 14:35:41 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd_2(char **words, int cd)
{
	if (ft_strcmp_2(words[1], "...", 1) == 0)
	{
		chdir("../..");
		if (cd == 0)
			return (0);
	}
	else if (ft_strcmp_2(words[1], "....", 1) == 0)
	{
		chdir("../../..");
		if (cd == 0)
			return (0);
	}
	else if (ft_strcmp_2(words[1], ".....", 1) == 0)
	{
		chdir("../../../..");
		if (cd == 0)
			return (0);
	}
	else if (ft_strcmp_2(words[1], "......", 1) == 0)
	{
		chdir("../../../../..");
		if (cd == 0)
			return (0);
	}
	return (1);
}

int	ft_cd(char **words, int cd)
{
	int i;

	i = 0;
	while (words[i])
		i++;
	if (!words[1] || ft_strcmp_2(words[1], "~", 1) == 0)
	{
		chdir("/");
		return (0);
	}
	else if (i > 3)
		printf("cd: too many arguments\n");
	else if (!words[2] && (ft_strcmp_2(words[1], "...", 1) == 0 ||
	ft_strcmp_2(words[1], "....", 1) == 0 || ft_strcmp_2(words[1], ".....", 1) == 0 ||
	ft_strcmp_2(words[1], "......", 1) == 0))
		return (ft_cd_2(words, cd));
	else if (!words[2] && chdir(words[1]) == -1)
	{
		printf("cd: %s: %s\n", strerror(errno), words[1]);
		if (cd == 0)
			return (0);
	}
	else if (i == 3)
	{
		printf("cd: string not in pwd: %s\n", words[1]);
		if (cd == 0)
			return (0);
	}
	return (1);
}
