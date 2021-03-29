/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:04:07 by minummin          #+#    #+#             */
/*   Updated: 2020/10/08 11:00:32 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_elem;
	t_list *new_list;

	new_list = NULL;
	while (lst)
	{
		if (!(new_elem = ft_lstnew(lst->content)))
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		f(new_elem->content);
		ft_lstadd_back(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}
