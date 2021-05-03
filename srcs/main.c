/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 09:32:22 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/03 20:39:37 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init(t_ls *data)
{
	data->envp = NULL;
	data->words = NULL;
	data->words1 = NULL;
	data->words2 = NULL;
	data->words3 = NULL;
	data->temp = NULL;
	data->line = NULL;
	data->lol = NULL;
	data->tmp_begin = NULL;
	data->c_e = NULL;
	data->p.pid = NULL;
	data->p.fd = NULL;
	data->ro.fd = NULL;
	data->ro.filename = NULL;
	data->ri.fd = NULL;
	data->ri.filename = NULL;
	data->bt.tmp = NULL;
	data->bt.rtn = NULL;
	data->exp.words = NULL;
	data->sys.path = NULL;
	data->sys.temp = NULL;
	data->sys.cmd = NULL;
	data->un2.tmp = NULL;
	data->un2.temp = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_v		*v;
	t_ls	data;
	t_term	t;

	ft_init(&data);
	ft_minishell_init(&t, &data);
	if (!argv)
		return (0);
	data.envp = envp;
	v = ft_lstnew_2(NULL);
	if (!v)
		ft_error_v(v);
	argc = (unsigned int)argc;
	ft_envp(v, envp);
	if (argc < 2)
		ft_print_prompt_3(300);
	if (argc >= 2)
		tester_lexer(v, &data, t, argv);
	else
		lexer(v, &data, t);
	return (0);
}
