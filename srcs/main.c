/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 09:32:22 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/22 16:56:11 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_envp(t_v *v, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		v->str = ft_strdup(envp[i]);
		if (!v->str)
			ft_error_v(v);
		v->next = ft_lstnew_2(NULL);
		if (!v->next)
			ft_error_v(v);
		v = v->next;
	}
}

void	ft_minishell_init(t_term *t, t_ls *data)
{
	t->i = 0;
	t->yo = NULL;
	t->w = NULL;
	t->count = 1;
	tcgetattr(0, &t->term);
	t->term.c_lflag &= ~(ECHO);
	t->term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &t->term);
	t->success = tgetent(NULL, getenv("TERM"));
	if (t->success < 0)
		printf("Could not access the termcap data base.\n");
	if (t->success == 0)
		printf("Terminal type `%s' is not defined.\n", getenv("TERM"));
	data->cd = 0;
	signal(SIGINT, main_signal_handler);
	signal(SIGQUIT, main_signal_handler);
	t->mark = 0;
	g_sigint = 1;
	data->statuscode = 0;
	t->w = (char **)malloc(sizeof(char *) * (1));
	t->w[0] = NULL;
}

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
	ft_print_prompt_2();
	ft_envp(v, envp);
	lexer(v, &data, tester, t);
	return (0);
}
