#include "../../includes/minishell.h"

void	unset_export(char **words, t_ls *data, t_v **v, char *temp)
{
	char	*tmp;
	t_v		*t;
	int		count;

	count = 1;
	while (words[count])
		count++;
	data->c_e = (char *)malloc(sizeof(char) * count);
	data->c_e[0] = 'm';
	temp = ft_strstr_reverse((*v)->str, "=");
	if (temp == NULL)
		temp = ft_strdup((*v)->str);
	tmp = ft_strstr_reverse(words[1], "=");
	if (tmp == NULL)
		tmp = ft_strdup(words[1]);
	if (ft_strcmp_2(tmp, temp, 1) == 0 && ft_strlen((*v)->str) > ft_strlen(words[1]))
	{
		data->c_e[1] = 'a';
		t = *v;
		ft_while_unset(words, *v, data);
		*v = (*v)->next;
		ft_lstdelone_2(t, ft_memdel);
	}
	else
	{
		data->c_e[1] = 'a';
		t = *v;
		ft_while_unset(words, t, data);
	}
	free(tmp);
	free(temp);
	data->c_e[count] = '\0';
}
