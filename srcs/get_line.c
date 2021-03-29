#include "../includes/minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	int	i;
	int	j;

	if (!s1 && !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	ft_memmove(str, s1, i);
	ft_memmove(str + i, s2, j);
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*ft_get_line_2(char *s)
{
	char    *str;
	int     i;
	int	j;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '"')
		{
			str[j] = s[i];
			j++;
			i++;
		}
		else
			i++;
	}
	str[j] = '\0';
	return (str);
}

int	ft_getline(char **line)
{
	char	*str;
	char	buff[33];
	int	ret;

	str = NULL;
	if (!line)
		return (-1);
	ret = 1;
	while (ret > 0 && !ft_strchr(str, '\n'))
	{
		if ((ret = read(0, buff, 32)) == -1)
			return (ft_free(&str));
		buff[ret] = '\0';
		if (!(str = ft_strjoin2(str, buff)))
			return (ft_free(&str));
	}
	if (ft_strchr(str, '"'))
	{
		if (!(*line = ft_get_line_2(str)))
			return (ft_free(&str));
		free(str);
		return (2);
	}
	if (!(*line = ft_get_line(str)))
		return (ft_free(&str));
	free(str);
	return (1);
}
