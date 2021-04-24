/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 09:32:22 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/22 21:38:44 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*tester;
	t_v		*v;
	t_ls	data;
	t_term	t;

	ft_minishell_init(&t, &data);
	if (!argv)
		return (0);
	//	if (argv[1][0] == '-' && argv[1][1] == 'c') // tester1
	//		tester = argv[2]; // tester1
	tester = NULL; // tester
	chdir(getenv("HOME"));
	data.envp = envp;
	v = ft_lstnew_2(NULL);
	if (!v)
		ft_error_v(v);
	argc = (unsigned int)argc;
	ft_print_prompt_2(data.statuscode);
	ft_envp(v, envp);
	lexer(v, &data, tester, t);
	return (0);
}
