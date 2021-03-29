/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:01:05 by minummin          #+#    #+#             */
/*   Updated: 2020/11/28 17:01:16 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *s)
{
	char	*str;
	int	len;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len] && s[len] != '\n')
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while (--len >= 0)
		str[len] = s[len];
	return (str);
}

static int	ft_strlen(char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_get_rest(char *s)
{
	char	*str;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!(str = (char *)malloc(sizeof(char) * ((ft_strlen(s) - i) + 1))))
		return (NULL);
	i++;
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

int	ft_return(char **s, int ret)
{
	if (ret == 0)
	{
		free(*s);
		return (0);
	}
	return (1);
}

int	ft_free(char **s)
{
	if (*s)
		free(*s);
	return (-1);
}
