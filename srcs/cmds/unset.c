/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:35:12 by minummin          #+#    #+#             */
/*   Updated: 2021/04/22 17:07:56 by minummin         ###   ########.fr       */
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

void	ft_unset2(char **words, t_v **v)
{
	char	*temp;
	t_v		*t;

	temp = NULL;
	if (*v)
	{
		temp = ft_strstr_reverse((*v)->str, "=");
		if (ft_strcmp_2(words[1], temp, 1) == 0)
		{
			t = *v;
			ft_while_unset(words, *v, NULL);
			*v = (*v)->next;
			ft_lstdelone_2(t, ft_memdel);
		}
		else
		{
			t = *v;
			ft_while_unset(words, t, NULL);
		}
		free(temp);
	}
}

void	ft_while_unset(char **words, t_v *v, char *temp)
{
	int	i;
	t_v	*t;

	while (v->next && v->next->next)
	{
		i = 0;
		while (words[++i])
		{
			if (v->next->str)
			{
				temp = ft_strstr_reverse(v->next->str, "=");
				if (ft_strcmp_2(words[i], temp, 1) == 0)
				{
					i = 0;
					t = v->next->next;
					ft_lstdelone_2(v->next, ft_memdel);
					v->next = t;
				}
				free(temp);
			}
		}
		v = v->next;
	}
}
