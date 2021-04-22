/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 10:36:18 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/16 11:22:26 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_3(t_term *t)
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

char	*lexer_2(t_term *t, char *str)
{
	int mark;

	mark = 0;
	lexer_3(t);
	if (t->errcode == 1)
		t->errcode = 0;
	while (t->mark == 0 || (ft_strcmp_2(str, "\n", 1) && ft_strcmp_2(str, "\4", 1)))
	{
		t->l = read(0, str, 100000);
		if ((int)str[0] == 4) // Ctrl + D
		{
			printf("exit\n");
			exit(1);
		}
		str[t->l] = '\0';
		if (g_sigint == 0)
		{
			t->errcode = 1;
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
	}
	t->mark = 0;
	return (t->yo);
}

void	lexer(t_v *v, t_ls *data, char *tester, t_term t)
{
	char	str[100000];
	int		z;
	int		in;

	in = 1;
	tester = NULL; // tester
	if (tester != NULL)
		return ;
	//	ret = 0; // tester1
	//	while (ret >= 0) // tester1
	while (ft_strcmp_2(str, "\4", 1) || in == 1)
	{
		in = 0;
		data->line = lexer_2(&t, str);
		if (t.errcode == 1)
			data->statuscode = 1;
		//		ret = -5; //tester1
		if (data->line[0] && data->line[0] != '\n')
		{
			if (!(data->words = shell_split(data->line, ';'))) // tester0
				//	if (!(data->words = shell_split(tester, ';'))) // tester1
				ft_error_data_v(data, v);
			z = -1;
			while (data->words[++z])
				if (!ft_pipe(v, data->words[z], data))
					infinity_loop(&v, data->words[z], data);
			z = -1;
			while (data->words[++z])
				free(data->words[z]);
			free(data->words);
		}
		if (g_sigint == 1)
			ft_print_prompt(data, v); // tester0
	}
}
