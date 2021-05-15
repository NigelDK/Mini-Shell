/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:04:27 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 13:04:11 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_check_flag(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '.' || str[i] == '0' || str[i] == '-')
		i++;
	if (str[i - 1] == '.')
		return (1);
	else if (str[i - 1] == '0')
	{
		if (str[i - 2] == '.' || str[i - 3] == '.')
			return (1);
		else if (str[i - 2] == '-')
			return (3);
		return (2);
	}
	else if (str[i - 1] == '-')
		return (3);
	return (0);
}

void	ft_check_width2(t_con *con, va_list valist)
{
	if (ft_check_true2(con->str) == 1)
	{
		if (*con->str == '*')
		{
			con->width2 = va_arg(valist, int);
			con->str++;
		}
		else
			con->width2 = ft_atoi_3(con);
	}
	else
		con->width2 = 0;
	if (con->width2 < 0)
	{
		con->flag2 = 0;
		con->flag_checker2 = 1;
		con->width2 = con->width2 * (-1);
	}
}

void	ft_check_width1(t_con *con, va_list valist)
{
	if (ft_check_true2(con->str) == 1)
	{
		if (*con->str == '*')
		{
			con->width1 = va_arg(valist, int);
			con->str++;
			if (*con->str - 48 >= 0 && *con->str - 48 < 10)
			{
				con->width1 = *con->str - 48;
				con->str++;
			}
		}
		else
			con->width1 = ft_atoi_3(con);
	}
	else
		con->width1 = 0;
	if (con->width1 < 0)
	{
		if (con->flag1 == 1)
			con->flag_checker = 1;
		con->flag1 = 3;
		con->width1 = con->width1 * (-1);
	}
}

int	ft_check_true2(char *str)
{
	while (*str != 's' && *str != 'u' && *str != 'c' && *str != 'd'
		&& *str != 'i' && *str != '%' && *str != 'p' && *str != 'X'
		&& *str != 'x' && *str)
	{
		if (*str == '-' || *str == '0' || *str == '.' || *str == '*'
			|| (*str - 48 > 0 && *str - 48 < 10))
			return (1);
		str++;
	}
	return (0);
}

int	ft_atoi_3(t_con *con)
{
	int	res;

	res = 0;
	while (*con->str - 48 >= 0 && *con->str - 48 < 10)
	{
		res = 10 * res + *con->str - 48;
		con->str++;
	}
	return (res);
}
