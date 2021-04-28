/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 09:32:22 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/28 16:48:49 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_v		*v;
	t_ls	data;
	t_term	t;

	ft_minishell_init(&t, &data);
	if (!argv)
		return (0);
	chdir(getenv("HOME"));
	data.envp = envp;
	v = ft_lstnew_2(NULL);
	if (!v)
		ft_error_v(v);
	argc = (unsigned int)argc;
	ft_print_prompt_2(data.statuscode);
	ft_envp(v, envp);
	lexer(v, &data, t);
	return (0);
}
