#include "../includes/minishell.h"

void	ft_error_split(char **line, char ***words)
{
	if (**words)
		free(**words);
	if (*line)
		free(*line);
	printf("Error: %s\n", strerror(errno));
	if (errno == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	ft_error(void)
{
	printf("Error: %s\n", strerror(errno));
	if (errno == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
