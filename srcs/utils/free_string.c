/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:30:43 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/04 12:30:50 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_string(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}

void	free_2d_string(char ***s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}
