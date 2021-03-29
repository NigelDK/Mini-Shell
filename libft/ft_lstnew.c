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
