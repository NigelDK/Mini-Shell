/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 10:36:18 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/22 21:37:30 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	str[0] = '\0';
	while (ft_strcmp_2(str, "\4", 1) || in == 1)
	{
		in = 0;
		data->line = ft_get_string(&t, str);
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
