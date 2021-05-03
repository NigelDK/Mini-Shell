/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:35:12 by minummin          #+#    #+#             */
/*   Updated: 2021/05/03 16:34:11 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_memdel(char *ap)
{
	if (ap)
	{
		free(ap);
		ap = NULL;
	}
}

void	ft_unset2(char **words, t_v **v, t_ls *data)
{
	t_v		*t;

	if (*v)
	{
		if (ft_strcmp_2(words[0], "export", 1) == 0)
			unset_export(words, data, v);
		else
		{
			data->un.temp = ft_strstr_reverse((*v)->str, "=");
			if (!data->un.temp)
				ft_error();
			if (ft_strcmp_2(words[1], data->un.temp, 1) == 0)
			{
				t = *v;
				ft_while_unset(words, *v, data);
				*v = (*v)->next;
				ft_lstdelone_2(t, ft_memdel);
			}
			else
			{
				t = *v;
				ft_while_unset(words, t, data);
			}
			free_string(&data->un.temp);
		}
	}
}

int	unset_del_1(char *words, t_v *v, int i, t_ls *data)
{
	t_v		*t;

	data->un.temp = ft_strstr_reverse(v->next->str, "=");
	if (data->un.temp == NULL)
	{
		data->un.temp = ft_strdup(v->next->str);
		if (!data->un.temp)
			ft_error();
	}
	data->un.tmp = ft_strstr_reverse(words, "=");
	if (data->un.tmp == NULL)
	{
		data->un.tmp = ft_strdup(words);
		if (!data->un.tmp)
			ft_error();
	}
	if (ft_strcmp_2(data->un.temp, data->un.tmp, 1) == 0 && ft_strlen(data->un.temp) < ft_strlen(words))
	{
		data->c_e[i] = 'a';
		i = 0;
		t = v->next->next;
		ft_lstdelone_2(v->next, ft_memdel);
		v->next = t;
	}
	else if (!ft_strcmp_2(data->un.tmp, data->un.temp, 1) && ft_strlen(data->un.temp) == ft_strlen(words))
		data->c_e[i] = 'b';
	else if (data->c_e[i] != 'b')
		data->c_e[i] = 'a';
	free_string(&data->un.tmp);
	free_string(&data->un.temp);
	return (i);
}

int	unset_del_2(char *words, t_v *v, int i, t_ls *data)
{
	t_v		*t;

	data->un.temp = ft_strstr_reverse(v->next->str, "=");
	if (data->un.temp == NULL)
	{
		data->un.temp = ft_strdup(v->next->str);
		if (!data->un.temp)
			ft_error();
	}
	if (ft_strcmp_2(words, data->un.temp, 1) == 0)
	{
		i = 0;
		t = v->next->next;
		ft_lstdelone_2(v->next, ft_memdel);
		v->next = t;
	}
	free_string(&data->un.temp);
	return (i);
}

void	ft_while_unset(char **words, t_v *v, t_ls *data)
{
	int	i;

	while (v->next && v->next->next)
	{
		i = 0;
		while (words[++i])
		{
			if (v->next->str)
			{
				if (ft_strcmp_2(words[0], "export", 1) == 0)
					i = unset_del_1(words[i], v, i, data);
				else
					i = unset_del_2(words[i], v, i, data);
			}
		}
		v = v->next;
	}
}
