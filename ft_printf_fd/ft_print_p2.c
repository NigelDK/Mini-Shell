/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:11:32 by minummin          #+#    #+#             */
/*   Updated: 2020/11/28 16:12:03 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_p_2(t_con *con, int strlen)
{
	if (con->flag1 == 0)
	{
		ft_space(con->width1 - strlen - 2, con);
		ft_putstr_3("0x", con);
		ft_putstr_3(con->string, con);
	}
	else if (con->flag1 == 1)
	{
		ft_putstr_3("0x", con);
		ft_zero(con->width1 - strlen, con);
		ft_putstr_3(con->string, con);
	}
	else if (con->flag1 == 2)
	{
		ft_putstr_3("0x", con);
		ft_zero(con->width1 - strlen - 2, con);
		ft_putstr_3(con->string, con);
	}
	else
	{
		ft_putstr_3("0x", con);
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - strlen - 2, con);
	}
}

void	ft_p_3(t_con *con, int strlen)
{
	ft_putstr_3("0x", con);
	ft_space(con->width2 - strlen, con);
	ft_putstr_3(con->string, con);
}

void	ft_p_4(t_con *con, int strlen)
{
	if (con->flag1 == 0 || con->flag1 == 2)
	{
		ft_space(con->width1 - con->width2 - 2, con);
		ft_putstr_3("0x", con);
		ft_zero(con->width2 - strlen, con);
		ft_putstr_3(con->string, con);
	}
	else if (con->flag1 == 3)
	{
		ft_putstr_3("0x", con);
		ft_zero(con->width2 - strlen, con);
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - con->width2 - 2, con);
	}
}

void	ft_p_5(t_con *con, int strlen)
{
	ft_putstr_3("0x", con);
	ft_zero(con->width2 - strlen, con);
	ft_putstr_3(con->string, con);
}

void	ft_p_6(t_con *con, int strlen)
{
	if (con->flag1 == 0)
	{
		ft_space(con->width1 - strlen - 2, con);
		ft_putstr_3("0x", con);
		ft_putstr_3(con->string, con);
	}
	else if (con->flag1 == 3)
	{
		ft_putstr_3("0x", con);
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - strlen - 2, con);
	}
}
