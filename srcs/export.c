#include "../includes/minishell.h"

void	ft_create_env(t_v *v, char *str)
{
	while (v->next)
		v = v->next;
	if (!(v->str = ft_strdup(str)))
		ft_error();
	if (!(v->next = ft_lstnew_2(NULL)))
		ft_error();
}

void	ft_export(char **words, t_v *v)
{
	if (words[1] == NULL)
		ft_lstiter_2(v);
	else if (ft_strchr(words[1], '=') && ft_isalpha(words[1][0]))
		ft_create_env(v, words[1]);
	else if (ft_isalpha(words[1][0]))
	{
		words[1] = ft_strjoin2(words[1], "=''");
		ft_create_env(v, words[1]);
	}
	else
		printf("export: not an identifier: %c\n", words[1][0]);
}
