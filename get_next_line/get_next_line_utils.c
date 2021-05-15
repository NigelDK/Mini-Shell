#include "get_next_line.h"

int     ft_free(char **s)
{
        if (*s)
        {
                free(*s);
                *s = NULL;
        }
        return (-1);
}

int     ft_strlen(char *s)
{
        int i;

        if (!s)
                return (0);
        i = 0;
        while (s[i])
                i++;
        return (i);
}

int     ft_strchr(char *s)
{
        int i;

        i = 0;
        if (!s)
                return (0);
        while (s[i])
        {
                if (s[i] == '\n')
                        return (1);
                i++;
        }
        return (0);
}
