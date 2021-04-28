/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cux_and_add_struct2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:07:11 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 13:16:45 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_x_conversion(t_con *con, va_list valist)
{
	int				strlen;
	unsigned int	n;

	n = va_arg(valist, unsigned int);
	con->integer = n;
	if (con->width1 == 0 && con->flag1 == 1 && n == 0)
		return ;
	if (con->conversion == 'X')
		con->string = ft_itoa_x(n, 1);
	else if (con->conversion == 'u')
		con->string = ft_itoa_u(n);
	else
		con->string = ft_itoa_x(n, 0);
	strlen = ft_strlen_3(con->string);
	if (con->width2 > 0 && con->flag_checker2 != 1)
		ft_con_width1andwidth2_vol5(con, strlen, 1);
	else
		ft_con_width1(con, strlen, 1);
	if (con->string)
		free(con->string);
}

void	ft_c_conversion(t_con *con, va_list valist)
{
	if (con->conversion == '%')
		con->c = '%';
	else if (con->conversion == 'c')
		con->c = va_arg(valist, int);
	ft_c_width1(con);
}

void	ft_c_width1(t_con *con)
{
	if (con->width1 > 1 && con->flag1 != 1)
	{
		if (con->flag1 == 0)
		{
			ft_space(con->width1 - 1, con);
			ft_putchar_3(con->c, con);
		}
		else if (con->flag1 == 2)
		{
			ft_zero(con->width1 - 1, con);
			ft_putchar_3(con->c, con);
		}
		else if (con->flag1 == 3)
		{
			ft_putchar_3(con->c, con);
			ft_space(con->width1 - 1, con);
		}
	}
	else
		ft_putchar_3(con->c, con);
}

void	ft_check_mike_count(t_con *con)
{
	while (*con->str == '.' || *con->str == '0' || *con->str == '-')
		con->str++;
}

char	ft_check_conversion(char *str)
{
	while (*str != 's' && *str != 'u' && *str != 'c' && *str != 'd'
		&& *str != 'i' && *str != '%' && *str != 'p' && *str != 'X'
		&& *str != 'x' && *str)
		str++;
	return (*str);
}
