/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:35:51 by minummin          #+#    #+#             */
/*   Updated: 2021/04/23 17:51:36 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **words)
{
	int	i;
	int	o;

	o = 1;
	if (ft_strcmp_2(words[1], "-n", 1) == 0)
		o = 2;
	i = 0;
	if (o == 2)
		i = 1;
	while (words[++i])
	{
		printf("%s", words[i]);
		if (words[i + 1])
			printf(" ");
	}
	if (o == 2)
		return ;
	printf("\n");
}
