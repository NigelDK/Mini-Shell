/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:35:51 by minummin          #+#    #+#             */
/*   Updated: 2021/04/16 10:03:30 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo_2(char *line, int c, int ret, char *line2)
{
	int mark;
	char *str;

	mark = 0;
	printf("dquote> ");
	fflush(stdout);
	str = ft_strdup(ft_strstr_2(line, "\""));
	while ((ret = ft_getline(&line2)) > 0)
	{
		mark = 1;
		c = ft_strlen(str);
		str[c] = '\n';
		if (ret == -1)
			ft_error();
		if (!(str = ft_strjoin2(str, line2)))
			ft_error();
		free(line2);
		if (ret == 2)
			break;
		printf("dquote> ");
		fflush(stdout);
	}
	printf("%s\n", str);
	free(str);
	return (mark);
}

int	ft_echo_3(char **words, t_v *v)
{
	char *temp;
	int mark;
	int i;

	i = 1;
	if (ft_strcmp_2(words[1], "-n", 1) == 0)
		i = 2;
	mark = 0;
	if (words[i] && words[i][0] == '$' && words[i][1])
	{
		while (v->next)
		{
			temp = ft_strstr_reverse(v->str, "=");
			if (ft_strcmp_2(words[i], temp, 0) == 0)
				mark = printf("%s", ft_strstr_2(v->str, "="));
			free(temp);
			v = v->next;
		}
	}
	return (mark);
}

void	ft_echo(char **words, t_v *v)
{
	int i;
	int o;
	int mark;

	o = 1;
	if (ft_strcmp_2(words[1], "-n", 1) == 0)
		o = 2;
	i = 0;
	if (o == 2)
		i = 1;
	mark = 0;
	if ((words[o] && words[o][0] == '$' && words[o][1]))
		mark = ft_echo_3(words, v);
	else
	{
		while (words[++i])
		{
			if (!words[i + 1])
				printf("%s", words[i]);
			else
				printf("%s ", words[i]);
		}
	}
	if (o == 2)
		return ;
	printf("\n");
}
