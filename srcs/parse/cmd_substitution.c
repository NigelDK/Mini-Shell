#include "../../includes/minishell.h"

//TRASH
void    cmd_substitution(t_ls *data, t_v **v)
{
	int		len;
	int		i;
	char	*tmp;

	i = -1;
	while (data->words2[++i])
	{
		len = (int)ft_strlen((data->words2[i]) - 1);
		if ((data->words2[i][0] == '`' && data->words2[i][len] == '`')
		|| (data->words2[i][0] == '$' && data->words2[i][1] == '(' && data->words2[i][len] == ')'))
		{
			if (data->words2[i][0] == '`')
				tmp = ft_substr(data->words2[i], 1, len - 1);
			else if (data->words2[i][0] == '$')
				tmp = ft_substr(data->words2[i], 2, len - 1);
		}
		free(data->words2[i]);
		infinity_loop(v, tmp, data);
		free(tmp);
	}
}