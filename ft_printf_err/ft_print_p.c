/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:10:32 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 13:19:56 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_p_conversion(t_con *con, va_list valist)
{
	int	strlen;

	con->pointer = va_arg(valist, void *);
	con->address = (unsigned long int)con->pointer;
	if (con->width1 == 0 && con->flag1 == 1 && con->integer == 0)
	{
		ft_putstr_3("0x", con);
		return ;
	}
	con->string = ft_itoa_for_p(con->address);
	strlen = ft_strlen_3(con->string);
	ft_p_conversion2(con, strlen);
}

void	ft_p_conversion2(t_con *con, int strlen)
{
	if ((con->width1 <= strlen + 2 || (con->width1 <= strlen
				&& con->flag1 == 1)) && con->width2 == 0)
		ft_p(con);
	else if (con->width2 == 0)
		ft_p_2(con, strlen);
	else if (con->width2 > 0 && con->flag1 == 1)
		ft_p_3(con, strlen);
	else if (con->width1 > con->width2 + 2 && con->width2 > strlen)
		ft_p_4(con, strlen);
	else if (con->width2 > con->width1 && con->width2 > strlen)
		ft_p_5(con, strlen);
	else if (con->width1 >= strlen && strlen >= con->width2)
		ft_p_6(con, strlen);
	else
		ft_p(con);
	if (con->string)
		free(con->string);
}

void	ft_p(t_con *con)
{
	ft_putstr_3("0x", con);
	ft_putstr_3(con->string, con);
}

char	*ft_itoa_for_p(unsigned long int n)
{
	char	*word;
	char	*hexa;
	int		i;
	int		count;

	if (n == 0)
		return (ft_strdup_3("0"));
	hexa = "0123456789abcdef";
	count = ft_counter(n, 16);
	word = (char *)malloc(sizeof(char) * count + 1);
	if (!word)
		return (NULL);
	i = count - 1;
	while (n > 0)
	{
		if (n % 16 < 10)
			word[i] = n % 16 + '0';
		else
			word[i] = hexa[n % 16];
		n = n / 16;
		i--;
	}
	word[count] = '\0';
	return (word);
}

int	ft_counter(unsigned long int n, unsigned long int size)
{
	int	count;

	count = 1;
	while (size <= n)
	{
		count++;
		n = n / size;
	}
	return (count);
}
