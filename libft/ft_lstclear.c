#include "libft.h"

void	ft_lstclear_2(t_v **lst, void (*del)(char *))
{
	t_v *temp;

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
