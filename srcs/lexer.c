/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 10:36:18 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/05 16:31:11 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer(t_v *v, t_ls data)
{
	char	*line;
	char	**words;
	int		ret;
	int		i;
	int		cd;

	cd = 0;
	while ((ret = get_next_line(0, &line)) >= 0)
	{
		if (line[0])
		{
			if (ret == -1)
				ft_error();
			if (!(words = shell_split(line, ';')))
				ft_error_split(&line, &words);
			i = -1;
			while (words[++i])
				if (!ft_pipe(v, words[i], &cd, data))
					infinity_loop(&v, words[i], &cd, data);
			i = -1;
			while (words[++i])
				free(words[i]);
			free(words);
		}
		ft_print_prompt(cd);
		free(line);
	}
}
