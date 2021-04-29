/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:39:59 by minummin          #+#    #+#             */
/*   Updated: 2021/04/29 11:45:54 by nde-koni         ###   ########.fr       */
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
