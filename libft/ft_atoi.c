/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:48:40 by minummin          #+#    #+#             */
/*   Updated: 2020/10/06 09:10:19 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_check(const char *str, int mark, int i)
{
	long res;

	res = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (res * 10 + str[i] - 48 < res && mark == -1)
			return (0);
		else if (res * 10 + str[i] - 48 < res && mark == 1)
			return (-1);
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res);
}

int			ft_atoi(const char *str)
{
	int i;
	int res;
	int mark;

	if (!str)
		return (0);
	i = 0;
	mark = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		mark = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	res = ft_check(str, mark, i);
	return ((int)res * mark);
}
