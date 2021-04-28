/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin </var/mail/minummin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:39:59 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 15:25:03 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(void)
{
	printf("Error: %s\n", strerror(errno));
	if (errno == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
