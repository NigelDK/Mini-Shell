#include "../../includes/minishell.h"

char	**ft_get_w(int *count, int *i, char *yo)
{
	static char *temppp[1000000];
	char **w;

	(*count)++;
	w = (char **)malloc(sizeof(char *) * *count);
	*i = 0;
	while (*i < *count - 1)
	{
		while (*i < *count - 2)
		{
			w[*i] = temppp[*i];
			(*i)++;
		}
		yo = ft_change_nl(yo);
		w[*i] = ft_strdup(yo);
		(*i)++;
	}
	w[*i] = NULL;
	*i = -1;
	while (w[++(*i)])
		temppp[*i] = w[*i];
	(*i)--;
	return (w);
}
