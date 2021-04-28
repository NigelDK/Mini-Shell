/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:15:07 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 13:12:15 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_i_d_conversion2(t_con *con, int mark, int strlen)
{
	con->string = ft_itoa_d(con->integer);
	if (con->integer == -2147483648)
		mark = 1;
	strlen = ft_strlen_3(con->string);
	if ((con->flag1 == 3 || con->flag1 == 0) && con->width1 == 1
		&& con->flag2 == 1 && con->width2 == 0 && con->integer != 0)
		ft_putstr_3(con->string, con);
	else if (con->width2 > 0 && con->flag_checker2 != 1)
		ft_con_width1andwidth2_vol5(con, strlen, mark);
	else
		ft_con_width1(con, strlen, mark);
	if (con->string)
		free(con->string);
}

void	ft_i_d_conversion(t_con *con, va_list valist)
{
	int	strlen;
	int	mark;

	mark = 1;
	con->integer = va_arg(valist, int);
	strlen = ft_words(con->integer);
	if (con->integer < 0)
	{
		if ((con->width1 >= strlen && con->flag1 != 0 && con->flag1 != 3)
			|| ((con->flag1 == 0 || con->flag1 == 2 || con->flag1 == 3)
				&& con->width2 > 0 && con->flag_checker2 != 1))
		{
			mark = -1;
			con->integer = con->integer * (-1);
		}
	}
	if (con->width1 == 0 && con->flag1 == 1 && con->integer == 0)
		return ;
	ft_i_d_conversion2(con, mark, strlen);
}

void	ft_con_width1_vol2(t_con *con, int strlen, int mark)
{
	if (con->flag1 == 2 && mark == -1)
	{
		if (con->flag2 == 1)
			ft_space(con->width1 - strlen - 1, con);
		ft_putchar_3('-', con);
		if (con->flag2 != 1)
			ft_zero(con->width1 - strlen - 1, con);
		ft_putstr_3(con->string, con);
	}
	else if (con->flag1 == 1 || con->flag1 == 2)
	{
		if (con->flag2 == 1 && con->flag1 == 1)
			return ;
		if (con->flag2 == 1)
			ft_space(con->width1 - strlen, con);
		else
			ft_zero(con->width1 - strlen, con);
		ft_putstr_3(con->string, con);
	}
	else if (con->flag1 == 3)
	{
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - strlen, con);
	}
}

void	ft_con_width1(t_con *con, int strlen, int mark)
{
	if (con->integer == 0 && con->flag1 != 1 && con->flag2 == 1
		&& con->width2 == 0)
		ft_space(con->width1, con);
	else if (con->width1 >= strlen && con->flag_checker != 1)
	{
		if (con->flag1 == 0)
		{
			ft_space(con->width1 - strlen, con);
			ft_putstr_3(con->string, con);
		}
		else if (con->flag1 == 1 && mark == -1)
		{
			ft_putchar_3('-', con);
			ft_zero(con->width1 - strlen, con);
			ft_putstr_3(con->string, con);
		}
		else if ((con->flag1 == 2 && mark == -1) || (con->flag1 == 1
				|| con->flag1 == 2) || (con->flag1 == 3))
			ft_con_width1_vol2(con, strlen, mark);
	}
	else
		ft_putstr_3(con->string, con);
}
