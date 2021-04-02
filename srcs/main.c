/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 09:32:22 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/02 16:15:39 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	infinity_loop(t_v *v, char *line, int *cd, t_ls data)
{
	int		i;
	char	**words;

	if (!(words = shell_split(line, ' ')))
		ft_error_split(&line, &words);
	if (ft_strcmp_2(words[0], "echo", 1) == 0)
		ft_echo(words, line, v);
	else if (ft_strcmp_2(words[0], "cd", 1) == 0)
		cd[0] = ft_cd(words, *cd);
	else if (ft_strcmp_2(words[0], "pwd", 1) == 0)
		ft_pwd();
	else if (ft_strcmp_2(words[0], "export", 1) == 0)
		ft_export(words, v);
	else if (ft_strcmp_2(words[0], "env", 1) == 0)
		ft_env(words, v);
	else
		sys_call(words, data);
	i = -1;
	while (words[++i])
		free(words[i]);
	free(words);
}

void	lexer(t_v *v, t_ls data)
{
	char	*line;
	char	**words;
	int		ret;
	int		i;
	int		cd;
	
	cd = 0;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (ret == -1)
			ft_error();
		if (!(words = shell_split(line, ';')))
			ft_error_split(&line, &words);
		i = -1;
		while (words[++i])
			infinity_loop(v, words[i], &cd, data);
		ft_print_prompt(cd);
		i = -1;
		while (words[++i])
			free(words[i]);
		free(words);
		free(line);
	}
}

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
	t_v 	v;
	t_ls	data;

	data.envp = envp; 
	v.str = NULL;
	v.next = NULL;
	argc = (unsigned int)argc;
	argv = NULL;
	ft_print_prompt_2();
	ft_envp(&v, envp);
	lexer(&v, data);
	return (0);
}
