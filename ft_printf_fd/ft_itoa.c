/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:08:41 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 15:03:19 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_itoa_u(unsigned int n)
{
	char	*word;
	int		i;
	int		count;

	if (n == 0)
		return (ft_strdup_3("0"));
	count = ft_counter(n, 10);
	word = malloc(sizeof(char) * count + 1);
	if (!word)
		return (NULL);
	i = count - 1;
	while (n > 0)
	{
		word[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	word[count] = '\0';
	return (word);
}

int	ft_words(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n = n * (-1);
		count++;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_strdup_3(char *s)
{
	char	*str;
	int		i;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa_d(int n)
{
	char	*word;
	int		i;
	int		count;

	if (n == 0)
		return (ft_strdup_3("0"));
	if (n == -2147483648)
		return (ft_strdup_3("-2147483648"));
	count = ft_words(n);
	word = malloc(sizeof(char) * count + 1);
	if (!word)
		return (NULL);
	if (n < 0)
	{
		word[0] = '-';
		n = n * -1;
	}
	i = count - 1;
	while (n > 0)
	{
		word[i--] = n % 10 + '0';
		n = n / 10;
	}
	word[count] = '\0';
	return (word);
}

char	*ft_itoa_x(unsigned int n, int count)
{
	char	*hexa;
	char	*word;
	int		i;

	if (n == 0)
		return (ft_strdup_3("0"));
	if (count == 0)
		hexa = "0123456789abcdef";
	else
		hexa = "0123456789ABCDEF";
	count = ft_counter(n, 16);
	word = (char *)malloc(sizeof(char) * count + 1);
	if (!word)
		return (NULL);
	i = count - 1;
	while (n > 0)
	{
		if (n % 16 > 9 && n % 16 < 16)
			word[i] = hexa[n % 16];
		else
			word[i--] = n % 16 + '0';
		n = n / 16;
	}
	word[count] = '\0';
	return (word);
}
