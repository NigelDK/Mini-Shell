/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:46:47 by minummin          #+#    #+#             */
/*   Updated: 2021/04/30 10:54:13 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	unset_export(char **words, t_ls *data, t_v **v, char *temp)
{
	char	*tmp;
	int		count;

	count = 1;
	while (words[count])
		count++;
	data->c_e = (char *)malloc(sizeof(char) * count);
	if (data->c_e == NULL)
		ft_error();
	data->c_e[0] = 'm';
	temp = ft_strstr_reverse((*v)->str, "=");
	if (temp == NULL)
		temp = ft_strdup((*v)->str);
	tmp = ft_strstr_reverse(words[1], "=");
	if (tmp == NULL)
		tmp = ft_strdup(words[1]);
	if (ft_strcmp_2(tmp, temp, 1) == 0
		&& ft_strlen((*v)->str) > ft_strlen(words[1]))
		unset_export_2(words, data, v);
	else
		unset_export_3(words, data, v);
	free(tmp);
	free(temp);
	data->c_e[count] = '\0';
}
