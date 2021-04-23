/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:35:51 by minummin          #+#    #+#             */
/*   Updated: 2021/04/23 12:41:37 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
void	ft_echo_3(char *words, t_v *v, int statuscode)
{
	char *temp;

	if (words[0] == '$')
	{
		if (words[1] == '?' && ft_isalpha(words[2]) == 0)
			printf("%d", statuscode);
		while (v->next)
		{
			temp = ft_strstr_reverse(v->str, "=");
			if (ft_strcmp_2(words, temp, 0) == 0)
				printf("%s", ft_strstr_2(v->str, "="));
			free(temp);
			v = v->next;
		}
	}
	else
		printf("%s", words);
}*/

void	ft_echo(char **words/*, t_v *v, int statuscode*/)
{
	int i;
	int o;

	o = 1;
	if (ft_strcmp_2(words[1], "-n", 1) == 0)
		o = 2;
	i = 0;
	if (o == 2)
		i = 1;
	while (words[++i])
	{
//		ft_echo_3(words[i], v, statuscode);
		printf("%s", words[i]);
		if (words[i + 1])
			printf(" ");
	}
	if (o == 2)
		return ;
	printf("\n");
}
