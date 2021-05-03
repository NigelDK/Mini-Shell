/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:35:51 by minummin          #+#    #+#             */
/*   Updated: 2021/05/03 16:36:56 by minummin         ###   ########.fr       */
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

void	ft_echo_2(int o)
{
	if (o >= 2)
		return ;
	printf("\n");
}

void	ft_echo_while(char **words, int i)
{
	while (words[++i])
	{
		printf("%s", words[i]);
		if (words[i + 1])
			printf(" ");
	}
}

void	ft_echo(char **words)
{
	int	i;
	int	o;
	int	a;

	a = 1;
	o = 1;
	if (!words[a])
	{
		printf("\n");
		return ;
	}
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
	ft_echo_while(words, i);
	ft_echo_2(o);
}
