/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:16:55 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 13:26:30 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_putstr_len(char *s, t_con *con, int len)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (len > i && s[i])
	{
		write(con->fd, &s[i], 1);
		i++;
		con->char_count++;
	}
}

void	ft_s_con2(t_con *con, int strlen)
{
	if (con->flag1 == 0)
	{
		ft_space(con->width1 - strlen, con);
		ft_putstr_3(con->string, con);
	}
	else if (con->flag1 == 1)
		ft_putstr_3(con->string, con);
	else if (con->flag1 == 2)
	{
		ft_zero(con->width1 - strlen, con);
		ft_putstr_3(con->string, con);
	}
	else
	{
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - strlen, con);
	}
}

void	ft_s_con3(t_con *con, int strlen)
{
	if (con->width2 >= strlen)
		ft_putstr_3(con->string, con);
	else
		ft_putstr_len(con->string, con, con->width2);
}

void	ft_s_con4(t_con *con, int strlen)
{
	if (con->flag1 == 0)
	{
		ft_space(con->width1 - strlen, con);
		ft_putstr_3(con->string, con);
	}
	else if (con->flag1 == 2)
	{
		ft_zero(con->width1 - strlen, con);
		ft_putstr_3(con->string, con);
	}
	else
	{
		ft_putstr_3(con->string, con);
		ft_space(con->width1 - strlen, con);
	}
}

void	ft_s_con5(t_con *con)
{
	if (con->flag1 == 0)
	{
		ft_space(con->width1 - con->width2, con);
		ft_putstr_len(con->string, con, con->width2);
	}
	else if (con->flag1 == 2)
	{
		ft_zero(con->width1 - con->width2, con);
		ft_putstr_len(con->string, con, con->width2);
	}
	else
	{
		ft_putstr_len(con->string, con, con->width2);
		ft_space(con->width1 - con->width2, con);
	}
}
