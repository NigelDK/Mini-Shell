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

int	ft_check_echo_flag(char *s)
{
	int	i;

	i = 1;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(char **words)
{
	int	i;
	int	o;
	int	a;

	a = 1;
	o = 1;
	if (!words[a])
		return ;
	while (words[a][0] == '-' && words[a][1] == 'n')
	{
		if (ft_check_echo_flag(words[a]) == 1)
			break ;
		a++;
		o++;
	}
	i = 0;
	if (o != 1)
		i = o - 1;
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
