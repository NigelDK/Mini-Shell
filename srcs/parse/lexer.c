/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 10:36:18 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/14 11:43:48 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer(t_v *v, t_ls *data, char *tester)
{
	int		ret;
	int		i;

	data->n_c = 0;
	data->cd = 0;
	tester = NULL; // tester
	if (tester != NULL)
		return;
//	ret = 0; // tester1
//	while (ret >= 0) // tester1
	while ((ret = get_next_line(0, &data->line)) >= 0) // tester0
	{
<<<<<<< HEAD
//		ret = -5; //tester1
=======
>>>>>>> dcbe629954d74f9f5d1d01b09af8c07bd2adf43a
		if (data->line[0])
		{
			if (ret == -1)
				ft_error_v(v);
			if (!(data->words = shell_split(data->line, ';'))) //tester0
//			if (!(data->words = shell_split(tester, ';'))) // tester1
				ft_error_data_v(data, v);
			i = -1;
			while (data->words[++i])
				if (!ft_pipe(v, data->words[i], data))
					infinity_loop(&v, data->words[i], data);
			i = -1;
			while (data->words[++i])
				free(data->words[i]);
			free(data->words);
		}
		free(data->line); //tester0
		ft_print_prompt(data, v); //tester0
	}
}
