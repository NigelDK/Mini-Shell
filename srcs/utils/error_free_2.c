/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:39:59 by minummin          #+#    #+#             */
/*   Updated: 2021/05/03 16:59:34 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(void)
{
	ft_printf_fd(2, "Error: %s\n", strerror(errno));
	if (errno == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

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
