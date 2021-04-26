/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin </var/mail/minummin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:46:14 by minummin          #+#    #+#             */
/*   Updated: 2021/04/23 19:35:18 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_history(t_term *t)
{
	if (t->yo && t->yo[0] != '\n')
	{
		if (t->w)
			free(t->w);
		t->w = ft_get_w(&t->count, &t->i, t->yo);
	}
	else
	{
		if (t->i != 0)
		{
			t->i = 0;
			while (t->w[t->i])
				t->i++;
			t->i--;
		}
	}
	t->n = t->i;
	t->mark = 0;
	t->a = 0;
	t->b = 0;
	tputs(save_cursor, 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
}

char	*ft_get_string_2(t_term *t, char *str)
{
	t->l = read(0, str, 100000);
	if ((int)str[0] == 4)
	{
		ft_eof(t);
		str[0] = '\0';
	}
	str[t->l] = '\0';
	if (g_sigint == 0)
	{
		t->mark = 1;
		t->errcode = 130;
		free(t->yo);
		t->yo = NULL;
		g_sigint = 1;
		t->i = 0;
		while (t->w[t->i])
			t->i++;
	}
	if (t->mark == 0)
	{
		free(t->yo);
		t->yo = NULL;
	}
	t->i = ft_print(t, str);
	t->mark = 1;
	return (str);
}

char	*ft_get_string(t_term *t, char *str)
{
	ft_get_history(t);
	if (t->errcode == 1)
		t->errcode = 0;
	while (t->mark == 0 || (ft_strcmp_2(str, "\n", 1)
			&& ft_strcmp_2(str, "\4", 1)))
		str = ft_get_string_2(t, str);
	t->mark = 0;
	return (t->yo);
}

void	ft_backspace(t_term *t)
{
	char	*temp;
	char	*temp2;

	if (t->a > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		(t->a)--;
		temp = ft_substr(t->yo, 0, t->a);
		temp2 = ft_substr(t->yo, t->a + 1, ft_strlen(t->yo));
		free(t->yo);
		t->yo = ft_strjoin2(temp, temp2);
		free(temp2);
	}
}

char	**ft_get_w(int *count, int *i, char *yo)
{
	static char	*temppp[1000000];
	char		**w;

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
		w[*i] = ft_strdup(yo);
		(*i)++;
	}
	w[*i] = NULL;
	*i = -1;
	while (w[++(*i)])
		temppp[*i] = w[*i];
	(*i)--;
	return (w);
}
