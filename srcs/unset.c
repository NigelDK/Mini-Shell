/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin </var/mail/minummin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:35:12 by minummin          #+#    #+#             */
/*   Updated: 2021/04/03 14:35:17 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_memdel(char *ap)
{
	if (ap)
	{
		free(ap);
		ap = NULL;
	}
}

void    ft_unset(char **words, t_v *v)
{
	int i;
	char *temp;
	t_v *t;

	temp = NULL;
	if (!words[1])
		printf("unset: not enough arguments\n");
	else
	{
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
}
