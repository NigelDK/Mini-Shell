/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:15:33 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 13:13:26 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_s_conversion(t_con *con, va_list valist)
{
	int	strlen;
	int	mark;

	mark = 0;
	con->string = va_arg(valist, char *);
	if (!con->string)
	{
		mark = 1;
		con->string = ft_strdup_3("(null)");
	}
	strlen = ft_strlen_3(con->string);
	ft_s_conversion2(con, strlen, mark);
}

void	ft_s_conversion2(t_con *con, int strlen, int mark)
{
	if (con->flag_checker2 == 1 && strlen >= con->width1)
		ft_putstr_3(con->string, con);
	else if (con->flag_checker2 == 1 && con->width1 > strlen)
		ft_s_con6(con, strlen);
	else if (con->flag_checker == 1)
		ft_putstr_3(con->string, con);
	else if (con->width2 == 0 && strlen >= con->width1 && con->flag2 != 1)
		ft_s_con(con);
	else if ((con->flag2 != 1 && con->width2 == 0 && con->width1 > strlen)
		|| (con->width2 > con->width1
			&& con->width2 > strlen && con->flag2 != 1))
		ft_s_con2(con, strlen);
	else if (con->flag1 == 1 && con->flag2 == 1)
		ft_s_con3(con, strlen);
	else if (con->width1 >= con->width2 && con->width2 > strlen)
		ft_s_con4(con, strlen);
	else if (con->width2 >= con->width1 && con->width1 > strlen)
		ft_s_con2(con, strlen);
	else
		ft_s_con5(con);
	if (mark == 1)
		free(con->string);
}

void	ft_s_con6(t_con *con, int strlen)
{
	if (con->flag1 == 3)
	{
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - strlen, con);
	}
	else
	{
		ft_space(con->width1 - strlen, con);
		ft_putstr_3(con->string, con);
	}
}

void	ft_s_con(t_con *con)
{
	if (con->flag1 == 0 || con->flag1 == 2 || con->flag1 == 3)
		ft_putstr_3(con->string, con);
	else if (con->flag1 == 1)
		ft_putstr_len(con->string, con, con->width1);
}
