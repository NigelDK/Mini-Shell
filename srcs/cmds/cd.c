/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:35:38 by minummin          #+#    #+#             */
/*   Updated: 2021/04/23 17:42:31 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **words, int cd, t_ls *data)
{
	int	i;
	int	mark;

	mark = 0;
	i = 0;
	while (words[i])
		i++;
	if (!words[1] || ft_strcmp_2(words[1], "~", 1) == 0)
	{
		data->statuscode = 0;
		chdir(getenv("HOME"));
		return (0);
	}
	else if ((!words[2] && chdir(words[1]) == -1) || i > 2)
	{
		mark = 1;
		data->statuscode = 500;
		printf("minishell: cd: %s: %s\n", words[1], strerror(errno));
		if (cd == 0)
			return (2);
	}
	if (mark != 1)
		data->statuscode = 0;
	return (1);
}
