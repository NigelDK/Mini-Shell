/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:47:16 by nde-koni          #+#    #+#             */
/*   Updated: 2021/05/12 14:19:33 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	change_home(t_ls *data, int i, t_v *v)
{
	char	*tmp;

	if (data->words2[i][1] == '\0')
		tmp = ft_strdup(getenv("HOME"));
	else
		tmp = ft_strjoin(getenv("HOME"),
				ft_substr(data->words2[i], 1, ft_strlen(data->words2[i])));
	if (!tmp)
		ft_error(data, &v);
	free_string(&data->words2[i]);
	data->words2[i] = tmp;
	return (0);
}

void	ft_print_env_2(t_v *v)
{
	while (v)
	{
		if (ft_strncmp(v->str, "_=", 2) == 0)
			printf("%s\n", v->str);
		v = v->next;
	}
}

void	ft_print_env_3(t_v *v)
{
	while (v)
	{
		if (v->str && (v->str[0] != '_' || v->str[1] != '=')
			&& ft_strchr(v->str, '='))
			printf("%s\n", v->str);
		v = v->next;
	}
}

void	ft_env(char **words, t_v *v, t_ls *data)
{
	if (words[1] == NULL)
	{
		ft_print_env_3(v);
		ft_print_env_2(v);
	}	
	else
	{
		ft_printf_fd(2, "env: %s: No such file or directory\n", words[1]);
		data->statuscode = 500;
	}
}
