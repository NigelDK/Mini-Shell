#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		prev_bslash(char *s, int k, int q)
{
	int	i;

	i = 0;
	if (s[k] == ' ' || q == 1)
		return (0); // protection for space
	while (--k >= 0 && s[k] == '\\')
		i++;
	return (i % 2);
}

static void	q_dq_index(char *s, int i, int *q, int *dq)
{
	if (s[i] == 39)
	{
		if (dq[0] == 1 || (q[0] == 0 && prev_bslash(s, i, *q)))
			q[0] = q[0];
		else if (q[0] == 0 && dq[0] == 0 && !prev_bslash(s, i, *q))
			q[0] = 1;
		else if (q[0] == 1)
			q[0] = 0;
	}
	if (s[i] == '"')
	{
		if (q[0] == 1 || prev_bslash(s, i, *q))
			dq[0] = dq[0];
		else if (dq[0] == 0 && q[0] == 0 && !prev_bslash(s, i, *q))
			dq[0] = 1;
		else if (dq[0] == 1 && q[0] == 0 && !prev_bslash(s, i, *q))
			dq[0] = 0;
	}
}

static int	trim_len(char *s)
{
	int	i;
	int	j;
	int	q;
	int	dq;

	i = 0;
	j = -1;
	q = 0;
	dq = 0;
	while (s[++j])
	{
/*		if (s[j] == 39)
		{
			if (dq == 1 || (q == 0 && prev_bslash(s, j, q)))
				q = q;
			else if (q == 0 && dq == 0 && !prev_bslash(s, j, q))
				q = 1;
			else if (q == 1)
				q = 0;
		}
		if (s[j] == '"')
		{
			if (q == 1 || prev_bslash(s, j, q))
				dq = dq;
			else if (dq == 0 && q == 0 && !prev_bslash(s, j, q))
				dq = 1;
			else if (dq == 1 && q == 0 && !prev_bslash(s, j, q))
				dq = 0;
		}*/
		if (s[j] == 39 && q == 0 && (dq == 1 || prev_bslash(s, j, q)))
			i++;
		else if (s[j] == '"' && q == 1)
			i++;
		else if (s[j] == '"' && q == 0 && prev_bslash(s, j, q))
			i++;
		else if (s[j] != 39 && s[j] != '"')
			i++;
		else if (s[j] == 39 && dq == 1)
			i++;
		q_dq_index(s, j, &q, &dq);
	}
	return (i);
}

static char	*trim_str(char *s)
{
	char	*rtn;
	int		len;
	int		i;
	int		j;
	int		q;
	int		dq;

	len = trim_len(s);
	if (!(rtn = malloc(sizeof(char) * (len + 1))))
		/*ft_error()*/;
	i = 0;
	j = 0;
	q = 0;
	dq = 0;
	while (s[j])
	{
/*		if (s[j] == 39)
		{
			if (dq == 1 || (q == 0 && prev_bslash(s, j, q)))
				q = q;
			else if (q == 0 && dq == 0 && !prev_bslash(s, j, q))
				q = 1;
			else if (q == 1)
				q = 0;
		}
		if (s[j] == '"')
		{
			if (q == 1 || prev_bslash(s, j, q))
				dq = dq;
			else if (dq == 0 && q == 0 && !prev_bslash(s, j, q))
				dq = 1;
			else if (dq == 1 && q == 0 && !prev_bslash(s, j, q))
				dq = 0;
		}*/
		if (s[j] == 39 && (dq == 1 || (q == 0 && prev_bslash(s, j, q))))
			rtn[i++] = s[j];
		else if (s[j] == '"' && q == 1)
			rtn[i++] = s[j];
		else if (s[j] == '"' && q == 0 && prev_bslash(s, j, q))
			rtn[i++] = s[j];
		else if (s[j] != 39 && s[j] != '"')
			rtn[i++] = s[j];
		q_dq_index(s, j, &q, &dq);
		j++;
		printf("%i || %i\n", q, dq);
	}
	rtn[i] = '\0';
	return (rtn);
}

int	main(int argc, char **argv)
{
	int		i;
	char	*tmp;

	tmp = malloc(sizeof(char) * 5);
	tmp[0] = '\'';
	tmp[1] = '\\';
	tmp[2] = '\'';
	tmp[3] = '\'';
	tmp[4] = '\0';
	i = trim_len(tmp);
	tmp = trim_str(tmp);
	printf("%s: %i\n", tmp, i);
}
