/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:46:47 by minummin          #+#    #+#             */
/*   Updated: 2021/05/04 12:59:12 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_del_lol(char *words, t_v *v, t_ls *data)
{
	if (data->un.temp == NULL)
	{
		data->un.temp = ft_strdup(v->next->str);
		if (!data->un.temp)
			ft_error(data, &v);
	}
	data->un.tmp = ft_strstr_reverse(words, "=");
	if (data->un.tmp == NULL)
	{
		data->un.tmp = ft_strdup(words);
		if (!data->un.tmp)
			ft_error(data, &v);
	}
}

void	unset_export_2(char **words, t_ls *data, t_v **v)
{
	t_v	*t;

	data->c_e[1] = 'a';
	t = *v;
	ft_while_unset(words, *v, data);
	*v = (*v)->next;
	ft_lstdelone_2(t, ft_memdel);
}

void	unset_export_3(char **words, t_ls *data, t_v **v)
{
	t_v	*t;

	data->c_e[1] = 'a';
	t = *v;
	ft_while_unset(words, t, data);
}

void	unset_export(char **words, t_ls *data, t_v **v)
{
	int		count;

	count = 1;
	while (words[count])
		count++;
	data->c_e = (char *)malloc(sizeof(char) * count);
	if (data->c_e == NULL)
		ft_error(data, v);
	data->c_e[0] = 'm';
	data->un2.temp = ft_strstr_reverse((*v)->str, "=");
	if (data->un2.temp == NULL)
		data->un2.temp = ft_strdup((*v)->str);
	data->un2.tmp = ft_strstr_reverse(words[1], "=");
	if (data->un2.tmp == NULL)
		data->un2.tmp = ft_strdup(words[1]);
	if (ft_strcmp_2(data->un2.tmp, data->un2.temp, 1) == 0
		&& ft_strlen((*v)->str) > ft_strlen(words[1]))
		unset_export_2(words, data, v);
	else
		unset_export_3(words, data, v);
	free_string(&data->un2.tmp);
	free_string(&data->un2.temp);
	data->c_e[count] = '\0';
}
