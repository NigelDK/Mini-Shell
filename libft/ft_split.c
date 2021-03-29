/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:08:54 by minummin          #+#    #+#             */
/*   Updated: 2020/10/06 11:05:42 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		count++;
	}
	if (s[i - 1] == c)
		return (count - 1);
	else
		return (count);
}

static int	ft_size(char *s, char c)
{
	int i;

	i = 0;
	while (*s && *s == c)
		s++;
	while (*s && *s != c)
	{
		s++;
		i++;
	}
	return (i);
}

static char	**ft_while(char **words, int count, char *str, char c)
{
	char	*word;
	int		nb;
	int		i;

	nb = 0;
	while (nb < count)
	{
		i = 0;
		while (*str && *str == c)
			str++;
		if (!(word = (char *)malloc(sizeof(char) * (ft_size(str, c) + 1))))
			return (NULL);
		while (str[i] && str[i] != c)
		{
			word[i] = str[i];
			i++;
		}
		while (*str && *str != c)
			str++;
		word[i] = '\0';
		words[nb] = word;
		nb++;
	}
	words[nb] = NULL;
	return (words);
}

char		**ft_split(char const *s, char c)
{
	char	**words;
	int		count;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	count = ft_word_count(str, c);
	if (!(words = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	return (ft_while(words, count, str, c));
}
