/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:35:38 by minummin          #+#    #+#             */
/*   Updated: 2021/04/08 20:59:27 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **words, int cd)
{
	int i;

	i = 0;
	while (words[i])
		i++;
	if (!words[1] || ft_strcmp_2(words[1], "~", 1) == 0)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else if (i > 3)
		printf("cd: too many arguments\n");
	else if (!words[2] && chdir(words[1]) == -1)
	{
		printf("cd: %s: %s\n", words[1], strerror(errno));
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
