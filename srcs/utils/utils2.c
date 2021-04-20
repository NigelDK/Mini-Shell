#include "../../includes/minishell.h"

char	*ft_change_nl(char *s1)
{
        int             i;

        if (!s1)
                return (NULL);
        i = 0;
        while (s1[i] != '\n' && s1[i] != '\0')
                i++;
        s1[i] = '\0';
        return (s1);
}
