/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:56:36 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/04 12:27:51 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_int(int **i)
{
	free(i[0]);
	i[0] = NULL;
}

void	free_tab_int(int ***i)
{
	int	j;

	j = 0;
	while (i[0][j])
		free(i[0][j++]);
	free(i[0]);
}
