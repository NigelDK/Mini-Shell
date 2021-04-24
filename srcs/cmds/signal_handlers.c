/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:51:54 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/23 17:48:50 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_signal_handler(int signr)
{
	if (signr == SIGINT)
	{
//		printf("\n");
		signal(SIGINT, child_signal_handler);
	}
}

void	main_signal_handler(int signr)
{
	if (signr == SIGINT)
	{
		printf("\n");
		ft_print_prompt_3(g_sigint);
		g_sigint = 0;
	}
	else if (signr == SIGQUIT)
	{
	//	ft_print_prompt_3();
	}
}
