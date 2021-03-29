#include "libft.h"

void	ft_lstdelone_2(t_v *lst, void (*del)(char *))
{
	if (!lst)
		return ;
	del(lst->str);
	free(lst);
}
