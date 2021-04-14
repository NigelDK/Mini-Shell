/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 09:32:22 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/14 11:44:01 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_envp(t_v *v, char **envp)
{
	int i;

	i = -1;
	while (envp[++i])
        {
                if (!(v->str = ft_strdup(envp[i])))
                        ft_error_v(v);
                if (!(v->next = ft_lstnew_2(NULL)))
                        ft_error_v(v);
		v = v->next;
        }
}

int	main(int argc, char **argv, char **envp)
{
	t_v 	*v;
	t_ls	data;
	char	*tester; // tester

	signal(SIGINT, main_signal_handler);
	if (!argv)
		return (0);
//	if (argv[1][0] == '-' && argv[1][1] == 'c') // tester1
//		tester = argv[2]; // tester1
	tester = NULL; // tester
	chdir("/");
	data.envp = envp; 
	if (!(v = ft_lstnew_2(NULL)))
		ft_error_v(v);
	argc = (unsigned int)argc;
	ft_print_prompt_2();
	ft_envp(v, envp);
	lexer(v, &data, tester);
	return (0);
}
