#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	is_redir_in(char *s, int j)
{
	if ((!s[j - 1] || s[j - 1] != '<') && s[j] == '<' &&
		(!s[j + 1] || s[j + 1] != '<'))
		return (1);
	return (0);
}

static int	redir_in_check(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (is_redir_in(s, i))
			return (1);
}

int	main(int argc, char **argv)
{
	int		i;
	char	*tmp;

	printf("%i\n", redir_in_check(argv[1]));
}
