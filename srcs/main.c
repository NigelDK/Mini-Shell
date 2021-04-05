/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 09:32:22 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/05 10:37:19 by nde-koni         ###   ########.fr       */
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
                        ft_error();
                if (!(v->next = ft_lstnew_2(NULL)))
                        ft_error();
		v = v->next;
        }
}

int	main(int argc, char **argv, char **envp)
{
	t_v 	*v;
	t_ls	data;

	chdir("/");
	data.envp = envp; 
	if (!(v = ft_lstnew_2(NULL)))
		ft_error();
	argc = (unsigned int)argc;
	argv = NULL;
	ft_print_prompt_2();
	ft_envp(v, envp);
	lexer(v, data);
	return (0);
}
