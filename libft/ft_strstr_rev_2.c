#include "libft.h"

char	*ft_strstr_rev_2(const char *s1, const char *s2)
{
	int i;
	int j;

	if (*s2 == 0 || s2 == 0)
		return ((char *)s1);
	i = ft_strlen(s1);
	i--;
	while (i >= 0)
	{
		j = 0;
		while (s1[i + j] == s2[j])
		{
			j++;
			if (s2[j] == 0)
				return ((char *)&s1[i + j]);
		}
		i -= j;
		i--;
	}
	return (0);
}
