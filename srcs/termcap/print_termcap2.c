#include "../../includes/minishell.h"

void	ft_eof(t_term *t)
{
	char	*temp;
	char	*temp2;

	if (ft_strlen(t->yo) == 0)
	{
		printf("exit\n");
		exit(1);
	}
	if (t->b > 0)
	{
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		(t->b)--;
		temp = ft_substr(t->yo, 0, t->a);
		temp2 = ft_substr(t->yo, t->a + 1, ft_strlen(t->yo));
		free(t->yo);
		t->yo = ft_strjoin2(temp, temp2);
		free(temp2);
	}
}
