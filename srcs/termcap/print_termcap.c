#include "../../includes/minishell.h"

void	ft_upperarrow(t_term *t)
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

void	ft_downarrow(t_term *t)
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

void	ft_leftrightarrow(t_term *t, char *str)
{
	if (!ft_strcmp_2(str, "\e[C", 1))
	{
		if (t->b > 0)
		{
			tputs(cursor_right, 1, ft_putchar);
			(t->a)++;
			(t->b)--;
		}
	}
	else if (!ft_strcmp_2(str, "\e[D", 1))
	{
		if (t->a > 0)
		{
			tputs(cursor_left, 1, ft_putchar);
			(t->a)--;
			(t->b)++;
		}
	}
}

void	ft_editline(t_term *t, char *str)
{
	char *temp;
	int c;

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

int     ft_print(t_term *t, char *str)
{
	char *temp;

	if (!ft_strcmp_2(str, "\e[A", 1))
		ft_upperarrow(t);
	else if (!ft_strcmp_2(str, "\e[B", 1))
		ft_downarrow(t);
	else if (!ft_strcmp_2(str, "\e[C", 1) || !ft_strcmp_2(str, "\e[D", 1))
		ft_leftrightarrow(t, str);
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
		ft_editline(t, str);
	return (t->i);
}
