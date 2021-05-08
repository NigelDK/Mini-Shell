/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:51:54 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/28 16:34:08 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_signal_handler(int signr)
{
	if (signr == SIGINT)
		signal(SIGINT, child_signal_handler);
}

void	main_signal_handler(int signr)
{
	if (signr == SIGINT)
	{
		if (g_sigint == 3)
			ft_printf_fd(1, "^C\n");
		else
			ft_printf_fd(1, "\n");
		g_sigint = 1;
		ft_print_prompt_3(g_sigint);
		g_sigint = 0;
	}
	else if (signr == SIGQUIT)
		return ;
}
