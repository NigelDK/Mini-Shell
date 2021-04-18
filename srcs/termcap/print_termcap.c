#include "../../includes/minishell.h"

void    ft_putchar_2(char c)
{
	write(1, &c, 1);
}

void    ft_putstr(char *s)
{
	int i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		write(1, &s[i], 1);
}

int     ft_print(t_term *t, char *str)
{
	char *temp;
	int c;

	if (!strcmp(str, "\e[A"))
	{
		if (t->i > 0 && t->mark != 0)
			t->i--;
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		ft_putstr(t->w[t->i]);
		t->a = ft_strlen(t->w[t->i]);
		t->b = 0;
		if (t->yo)
		{
			free(t->yo);
			t->yo = NULL;
		}
		t->yo = ft_strjoin2(t->yo, t->w[t->i]);
	}
	else if (!strcmp(str, "\e[B"))
	{
		if (t->i < t->n + 1)
			t->i++;
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		if (t->i != t->n + 1)
		{
			ft_putstr(t->w[t->i]);
			t->a = ft_strlen(t->w[t->i]);
			t->b = 0;
		}
		else
			t->a = 0;
		if (t->yo)
		{
			free(t->yo);
			t->yo = NULL;
		}
		if (t->i != t->n + 1)
			t->yo = ft_strjoin2(t->yo, t->w[t->i]);
		else
			t->b = 0;
	}
	else if (!strcmp(str, "\e[C"))
	{
		if (t->b > 0)
		{
			tputs(cursor_right, 1, ft_putchar);
			(t->a)++;
			(t->b)--;
		}
	}
	else if (!strcmp(str, "\e[D"))
	{
		if (t->a > 0)
		{
			tputs(cursor_left, 1, ft_putchar);
			(t->a)--;
			(t->b)++;
		}
	}
	else if ((int)str[0] == 127)
	{
		if (t->a > 0)
		{
			tputs(cursor_left, 1, ft_putchar);
			tputs(tgetstr("dc", NULL), 1, ft_putchar);
			(t->a)--;
			temp = ft_substr(t->yo, 0, t->a);
			t->yo = ft_strjoin2(ft_substr(t->yo, t->a + 1, ft_strlen(t->yo)), temp);
		}
	}
	else
	{
		if (t->b == 0)
		{
			tputs(str, 1, ft_putchar);
			t->yo = ft_strjoin2(t->yo, str);
			t->b = 0;
			(t->a)++;
		}
		else
		{
			c = ft_strlen(t->yo) - t->a + 1;
			temp = ft_substr(t->yo, t->a, ft_strlen(t->yo));
			tputs(str, 1, ft_putchar);
			tputs(temp, 1, ft_putchar);
			t->yo = ft_strjoin2(ft_change_nl(ft_strjoin2(ft_substr(t->yo, 0, t->a), str)), temp);
			while (--c > 0)
				tputs(cursor_left, 1, ft_putchar);
			(t->a)++;
		}
	}
	return (t->i);
}

char    **ft_get_w(int *count, int *i, char *yo)
{
	static char *temppp[1000000];
	char **w;

	(*count)++;
	w = (char **)malloc(sizeof(char *) * *count);
	*i = 0;
	while (*i < *count - 1)
	{
		while (*i < *count - 2)
		{
			w[*i] = temppp[*i];
			(*i)++;
		}
		yo = ft_change_nl(yo);
		w[*i] = strdup(yo);
		(*i)++;
	}
	w[*i] = NULL;
	*i = -1;
	while (w[++(*i)])
		temppp[*i] = w[*i];
	(*i)--;
	return (w);
}

char    *ft_change_nl(char *s1)
{
	int             i;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\n' && s1[i] != '\0')
		i++;
	s1[i] = '\0';
	return (s1);
}

int     ft_putchar(int c)
{
	return (write(1, &c, 1));
}
