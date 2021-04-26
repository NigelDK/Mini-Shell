/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:48:07 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/26 17:11:20 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int	syntax_error_check(t_ls *data)
{
	int i;
	
	i = 0;
	while (data->line[i] == ' ')
		i++;
	if (data->line[i] == '|' || data->line[i] == ';')
	{
		printf("bash: syntax error near unexpected token `%c'\n",
				data->line[i]);
		return (1);
	}
	return (0);
}