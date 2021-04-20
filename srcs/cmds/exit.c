#include "../../includes/minishell.h"

int	ft_strisnum(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (ft_isdigit(s[i]) == 0)
			return (0);
	return (1);
}

void	ft_exit(char **words, t_v **v, char *temp)
{
	int i;

/*	if (words[1] && words[2])
	{
		printf("exit: too many arguments\n");
		return ;
	}*/
	i = -1;
	free(temp);
	ft_lstclear_2(v, ft_memdel);
	if (words[1]  && ft_strisnum(words[1]) == 0)
	{
		printf("exit: %s: numeric argument required\n", words[1]);
		while (words[++i])
			free(words[i]);
		free(words);
		exit(255);
	}
	else if (words[1] && !words[2])
	{
		printf("exit\n");
		exit(ft_atoi(words[1]));
		while (words[++i])
			free(words[i]);
		free(words);
	}
	else
	{
		printf("exit\n");
		while (words[++i])
			free(words[i]);
		free(words);
		exit(0);
	}
}
