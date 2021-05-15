#include "checker.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static long     ft_checkeri(const char *str, int mark, int i)
{
	long    res;

	res = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (res * 10 + str[i] - 48 < res && mark == -1)
			return (0);
		else if (res * 10 + str[i] - 48 < res && mark == 1)
			return (-1);
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res);
}

long     ft_atoi(const char *str)
{
	int     i;
	long     res;
	int     mark;

	if (!str)
		return (0);
	i = 0;
	mark = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		mark = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	res = ft_checkeri(str, mark, i);
	return ((long)res * mark);
}

int	ft_isnumber(char *s, t_v *v, t_all *t)
{
	int	i;
	long	a;

	if (!s)
		return (0);
	a = ft_atoi(s);
	if (a > 2147483647 || a < -2147483648)
		exit(ft_fail("Error", 2, t, v));
	i = -1;
	if (s[0] == '-')
		i++;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			return (0);
	return (1);
}

int	ft_fail(char *s, int k, t_all *t, t_v *v)
{
	if (k == 1)
		free(t->stack_a);
	else if (k == 3)
	{
		free(t->stack_a);
		free(t->stack_b);
	}
	else if (k == 2)
	{
		free(t->stack_a);
		free(t->stack_b);
	}
	ft_lstclear(&v, ft_memdel);
	ft_printf_fd(2, "%s\n", s);
	return (1);
}

char	*ft_strdup(char *s1)
{
	char	*str;
	int		i;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}
