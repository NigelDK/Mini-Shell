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

int	ft_cd(char **words, int cd)
{
	if (ft_strcmp_2(words[1], NULL, 1) == 0)
	{
		chdir("/Users/mikkonumminen/19/project_minishell");
		return (0);
	}
	if (chdir(words[1]) == -1)
	{
		printf("cd: %s: %s, %d\n", strerror(errno), words[1], errno);
		if (cd == 0)
			return (0);
	}
	return (1);
}
