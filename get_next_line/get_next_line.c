#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char *str;
	char buf[2];
	int ret;

	ret = 1;
	while (ret > 0 && !ft_strchr(str))
	{
		if ((ret = read(fd, buf, 1)) == -1)
			return (ft_free(&str));
		buf[ret] = '\0';
		if (!(str = ft_strjoin(str, buf)))
			return (ft_free(&str));
	}
	if (!(*line = ft_get_line(str)))
		return (-1);
	str = ft_get_rest(str);
	if (ret == 0)
		return (0);
	return (1);	
}

char	*ft_get_rest(char *s)
{
	char *str;
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	if (!(str = (char *)malloc(sizeof(char) * ((ft_strlen(s) - i) + 1))))
		return (NULL);
	i++;
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

char	*ft_get_line(char *s)
{
	char *str;
	int i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	while (--i >= 0)
		str[i] = s[i];
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int i;
	int j;
	char *str;

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

void	*ft_memmove(char *dest, char *src, int len)
{
	unsigned char *d;
	unsigned char *s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d == s || (d == NULL && s == NULL))
		return (NULL);
	while (len--)
		d[len] = s[len];
	return (dest);
}
