/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:47:16 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/29 12:11:48 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_env_2(t_v *v)
{
	while (v)
	{
		if (ft_strncmp(v->str, "_=", 2) == 0)
			printf("%s\n", v->str);
		v = v->next;
	}
}

void    ft_print_env_3(t_v *v)
{
        while (v)
        {
		if (v->str && (v->str[0] != '_' || v->str[1] != '='))
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
