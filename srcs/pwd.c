#include "../includes/minishell.h"

void	ft_pwd(void)
{
	long size;
	char *buf;
	char *ptr;

	size = pathconf(".", _PC_PATH_MAX);
	if (!(buf = (char *)malloc((size_t)size)))
		ft_error();
	ptr = getcwd(buf, (size_t)size);
	printf("%s\n", ptr);
	free(ptr);
}
