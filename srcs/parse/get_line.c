/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:36:55 by minummin          #+#    #+#             */
/*   Updated: 2021/04/23 22:07:10 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, i);
	ft_memmove(str + i, s2, j);
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*ft_get_line_2(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i] && s[i] != '\n')
	{
		if (s[i] != '"')
		{
			str[j] = s[i];
			j++;
		}
	}
	str[j] = '\0';
	return (str);
}

int	ft_getline_2(char *str, char ***line)
{
	if (ft_strchr(str, '"'))
	{
		**line = ft_get_line_2(str);
		if (**line == NULL)
			return (ft_free(&str));
		free(str);
		return (2);
	}
	**line = ft_get_line(str);
	if (**line == NULL)
		return (ft_free(&str));
	free(str);
	return (1);
}

int	ft_getline(char **line)
{
	char	*str;
	char	buff[33];
	int		ret;

	str = NULL;
	if (!line)
		return (-1);
	ret = 1;
	while (ret > 0 && !ft_strchr(str, '\n'))
	{
		ret = read(0, buff, 32);
		if (ret == -1)
			return (ft_free(&str));
		buff[ret] = '\0';
		str = ft_strjoin2(str, buff);
		if (!str)
			return (ft_free(&str));
	}
	return (ft_getline_2(str, &line));
}
