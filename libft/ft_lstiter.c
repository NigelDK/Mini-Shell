#include "libft.h"

void	ft_lstiter_2(t_v *v)
{
	while (v)
	{
		if (v->str)
			printf("%s\n", v->str);
		v = v->next;
	}
}
