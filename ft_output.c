/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:48 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 13:15:03 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_putchar(char c, t_con *con)
{
	write(2, &c, 1);
	con->char_count++;
}

void	ft_zero(int a, t_con *con)
{
	while (a > 0)
	{
		write(2, "0", 1);
		con->char_count++;
		a--;
	}
}

void	ft_space(int b, t_con *con)
{
	while (b > 0)
	{
		write(2, " ", 1);
		con->char_count++;
		b--;
	}
}

void	ft_putstr(char *s, t_con *con)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		con->char_count++;
		i++;
	}
}

int	ft_strlen(char *s)
{
	int	i;

	if (s == 0 || *s == 0)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
