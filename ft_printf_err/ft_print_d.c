/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:12:23 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 13:05:52 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_con_width1andwidth2_vol9(t_con *con, int strlen, int mark)
{
	if (mark == -1)
	{
		ft_putchar_3('-', con);
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - strlen - 1, con);
	}
	else
	{
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - strlen, con);
	}
}

void	ft_con_width1andwidth2(t_con *con, int strlen, int mark)
{
	if (con->flag1 == 0 || con->flag1 == 2)
	{
		if (mark == -1)
		{
			ft_space(con->width1 - strlen - 1, con);
			ft_putchar_3('-', con);
		}
		else
			ft_space(con->width1 - strlen, con);
		ft_putstr_3(con->string, con);
	}
	else if (con->flag1 == 1)
		ft_putstr_3(con->string, con);
	else if (con->flag1 == 3)
		ft_con_width1andwidth2_vol9(con, strlen, mark);
}

void	ft_con_width1andwidth2_vol2(t_con *con, int strlen, int mark)
{
	if (con->flag1 == 3 && con->flag2 == 0)
	{
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - strlen, con);
	}
	else if ((con->flag1 == 0 || con->flag1 == 2) && mark == -1)
	{
		ft_space(con->width1 - con->width2 - 1, con);
		ft_putchar_3('-', con);
		ft_zero(con->width2 - strlen, con);
		ft_putstr_3(con->string, con);
	}
	else if (con->flag1 == 0 || con->flag1 == 2)
	{
		ft_space(con->width1 - con->width2, con);
		ft_zero(con->width2 - strlen, con);
		ft_putstr_3(con->string, con);
	}
}

void	ft_con_width1andwidth2_vol3(t_con *con, int strlen, int mark)
{
	if (con->flag1 == 1)
	{
		if (mark == -1)
			ft_putchar_3('-', con);
		ft_zero(con->width2 - strlen, con);
		ft_putstr_3(con->string, con);
	}
	else if (con->flag1 == 3 && mark == -1)
	{
		ft_putchar_3('-', con);
		ft_zero(con->width2 - strlen, con);
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - con->width2 - 1, con);
	}
	else if (con->flag1 == 3)
	{
		ft_zero(con->width2 - strlen, con);
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - con->width2, con);
	}
}

void	ft_con_width1andwidth2_vol5(t_con *con, int strlen, int mark)
{
	if (strlen >= con->width2 && strlen >= con->width1)
	{
		if (mark == -1)
			ft_putchar_3('-', con);
		ft_putstr_3(con->string, con);
	}
	else if (strlen >= con->width2 && strlen < con->width1)
		ft_con_width1andwidth2(con, strlen, mark);
	else if (con->width1 >= con->width2 && con->width2 > strlen)
	{
		ft_con_width1andwidth2_vol2(con, strlen, mark);
		ft_con_width1andwidth2_vol3(con, strlen, mark);
	}
	else if ((con->width2 >= con->width1 && con->width2 > strlen)
		|| (con->width2 > con->width1 && strlen > con->width1))
	{
		if (con->flag2 == 1)
		{
			if (mark == -1)
				ft_putchar_3('-', con);
			ft_zero(con->width2 - strlen, con);
			ft_putstr_3(con->string, con);
		}
	}
}
