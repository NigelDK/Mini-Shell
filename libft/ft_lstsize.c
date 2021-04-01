#include "libft.h"

int	ft_lstsize_2(t_v *lst)
{
	int count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
