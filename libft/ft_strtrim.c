/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:13:32 by minummin          #+#    #+#             */
/*   Updated: 2020/10/06 09:57:18 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char c, char const *set)
{
	int i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

static char	*ft_yee(char const *s1, char *str, int len, int i)
{
	int k;

	k = 0;
	while (len > k)
	{
		str[k] = s1[i];
		k++;
		i++;
	}
	str[k] = '\0';
	return (str);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1) - 1;
	while (ft_check(s1[i], set) == 1)
		i++;
	while (j > 0 && ft_check(s1[j], set) == 1)
		j--;
	if (j == 0)
		j = i;
	len = j - i + 1;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	return (ft_yee(s1, str, len, i));
}
