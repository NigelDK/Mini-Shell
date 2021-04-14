/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 10:36:18 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/12 14:07:55 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer(t_v *v, t_ls *data)
{
	int		ret;
	int		i;

	data->n_c = 0;
	data->cd = 0;
	while ((ret = get_next_line(0, &data->line)) >= 0)
	{
		if (data->line[0])
		{
			if (ret == -1)
				ft_error_v(v);
			if (!(data->words = shell_split(data->line, ';')))
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
		free(data->line);
		ft_print_prompt(data, v);
	}
}
