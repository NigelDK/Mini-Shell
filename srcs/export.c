/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin </var/mail/minummin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:36:33 by minummin          #+#    #+#             */
/*   Updated: 2021/04/03 14:36:37 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_export_2(char **words, int count)
{
	int i;
	int j;
	char *str;

	i = -1;
	while (++i < count - 2)
	{
		j = i + 1;
		if (ft_strcmp_2(words[i], words[j], 1) >= 0)
		{
			str = words[i];
			words[i] = words[j];
			words[j] = str;
			i = -1;
		}
	}
	i = -1;
	while (words[++i])
		if (words[i][0] != '_' || words[i][1] != '=')
			printf("%s\n", words[i]);
}

void	ft_print_export(t_v *v)
{
	char **words;
	int i;
	int count;

	i = 0;
	count = ft_lstsize_2(v);
	if (!(words = (char **)malloc(sizeof(char *) * count)))
		ft_error();
	while (v)
	{
		words[i] = ft_strdup(v->str);
		i++;
		v = v->next;
	}
	ft_print_export_2(words, count);
	i = -1;
	while (words[++i])
		free(words[i]);
	free(words);
}

void	ft_create_env(t_v *v, char *str)
{
	while (v->next)
		v = v->next;
	if (!(v->str = ft_strdup(str)))
		ft_error();
	if (!(v->next = ft_lstnew_2(NULL)))
		ft_error();
}

void	ft_export(char **words, t_v *v)
{
	if (words[1] == NULL)
		ft_print_export(v);
	else if (ft_strchr(words[1], '=') && ft_isalpha(words[1][0]))
		ft_create_env(v, words[1]);
	else if (ft_isalpha(words[1][0]))
	{
		words[1] = ft_strjoin2(words[1], "=''");
		ft_create_env(v, words[1]);
	}
	else
		printf("export: not an identifier: %c\n", words[1][0]);
}
