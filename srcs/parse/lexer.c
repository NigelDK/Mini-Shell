/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 10:36:18 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/12 14:47:27 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_2(t_v **v, t_ls *data, t_term t)
{
	int	z;

	if (t.errcode == 1)
		data->statuscode = 1;
	if (data->line[0] && data->line[0] != '\n' && !syntax_error_check(data))
	{
		data->words = shell_split(data->line, ';');
		if (!data->words)
			ft_error_data_v(data, *v);
		z = -1;
		while (data->words[++z])
		{
			if (data->words[z][0] == '\n')
				continue ;
			if (!ft_pipe(*v, &data->words[z], data))
				infinity_loop(v, data->words[z], data);
		}
		z = -1;
		while (data->words[++z])
			free(data->words[z]);
		free(data->words);
	}
	if (g_sigint == 1)
		ft_print_prompt(data, *v);
}

void	lexer(t_v *v, t_ls *data, t_term t)
{
	char	str[100000];
	int		in;

	in = 1;
	str[0] = '\0';
	g_sigint = 1;
	while (ft_strcmp_2(str, "\4", 1) || in == 1)
	{
		in = 0;
		tcgetattr(0, &t.termioush);
		t.term = t.termioush;
		t.term.c_lflag &= ~(ECHO);
		t.term.c_lflag &= ~(ICANON);
		t.termioush.c_cc[VEOF] = 4;
		tcsetattr(0, TCSANOW, &t.term);
		t.success = tgetent(NULL, getenv("TERM"));
		if (t.success < 0)
			ft_printf_fd(2, "Could not access the termcap data base.\n");
		if (t.success == 0)
			ft_printf_fd(2, "Terminal type is not defined.\n");
		data->line = ft_get_string(&t, str);
		tcsetattr(0, TCSANOW, &t.termioush);
		lexer_2(&v, data, t);
	}
}
