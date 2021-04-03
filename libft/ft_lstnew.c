/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin </var/mail/minummin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:40:50 by minummin          #+#    #+#             */
/*   Updated: 2021/04/03 14:40:52 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_v	*ft_lstnew_2(char *content)
{
	t_v *new;

	if (!(new = malloc(sizeof(t_v))))
		return (NULL);
	new->str = content;
	new->next = NULL;
	return (new);
}
