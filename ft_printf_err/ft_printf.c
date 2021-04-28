/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:17:22 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 13:05:04 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_printf_fd(int fd, const char *format, ...)
{
	t_con	con;
	va_list	valist;

	con.fd = fd;
	con.char_count = 0;
	va_start(valist, format);
	con.str = (char *)format;
	ft_while(&con, valist);
	va_end(valist);
	return (con.char_count);
}

void	ft_while(t_con *con, va_list valist)
{
	while (*con->str != '\0')
	{
		if (*con->str == '%')
			ft_add_cons(con, valist);
		else
		{
			write(con->fd, &*con->str, 1);
			con->str++;
			con->char_count++;
		}
	}
}

void	ft_add_cons(t_con *con, va_list valist)
{
	con->str++;
	con->conversion = ft_check_conversion(con->str);
	if (con->conversion != '\0')
	{
		con->flag_checker2 = 0;
		con->flag_checker = 0;
		con->flag1 = 0;
		con->flag2 = 0;
		con->width1 = 0;
		con->width2 = 0;
		if (ft_check_true2(con->str) == 1)
		{
			con->flag1 = ft_check_flag(con->str);
			ft_check_mike_count(con);
			ft_check_width1(con, valist);
			if (*con->str == '.' || *con->str == '0' || *con->str == '-')
			{
				con->flag2 = ft_check_flag(con->str);
				ft_check_mike_count(con);
				ft_check_width2(con, valist);
			}
		}
		ft_check(valist, con);
		con->str++;
	}
}

void	ft_check(va_list valist, t_con *con)
{
	if (*con->str == 'p')
		ft_p_conversion(con, valist);
	else if (*con->str == '%')
		ft_c_conversion(con, valist);
	else if (*con->str == 'x')
		ft_x_conversion(con, valist);
	else if (*con->str == 'c')
		ft_c_conversion(con, valist);
	else if (*con->str == 'X')
		ft_x_conversion(con, valist);
	else if (*con->str == 'i' || *con->str == 'd')
		ft_i_d_conversion(con, valist);
	else if (*con->str == 's')
		ft_s_conversion(con, valist);
	else if (*con->str == 'u')
		ft_x_conversion(con, valist);
}
