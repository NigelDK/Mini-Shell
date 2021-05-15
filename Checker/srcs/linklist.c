#include "checker.h"

void	ft_memdel(char *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
}

void	ft_lstclear(t_v **lst, void (*del)(char *))
{
	t_v	*temp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->str);
		free(*lst);
		*lst = temp;
	}
}

t_v	*ft_lstnew(char *content)
{
	t_v	*new;

	new = malloc(sizeof(t_v));
	if (!new)
		return (NULL);
	new->str = content;
	new->next = NULL;
	return (new);
}
