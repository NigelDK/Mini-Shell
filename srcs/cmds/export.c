/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:36:33 by minummin          #+#    #+#             */
/*   Updated: 2021/05/03 17:02:20 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_some(char *word)
{
	int	i;

	if (!word)
		return ;
	ft_putstr("declare -x ");
	i = -1;
	while (word[++i] && word[i] != '=')
		ft_putchar_2(word[i]);
	if (word[i] != '=')
	{
		ft_putchar_2('\n');
		return ;
	}
	ft_putchar_2(word[i++]);
	ft_putstr("\"");
	while (word[i])
	{
		ft_putchar_2(word[i]);
		i++;
	}
	ft_putstr("\"");
	ft_putchar_2('\n');
}	

void	ft_print_export_2(char **words, int count, int mark)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	while (++i < count - 2)
	{
		j = i + 1;
		if (ft_strcmp_2(words[i], words[j], 1) > 0)
		{
			str = words[i];
			words[i] = words[j];
			words[j] = str;
			i = -1;
		}
	}
	i = -1;
	if (mark == 0)
		while (words[++i])
			ft_print_some(words[i]);
	else
		while (words[++i])
			if (words[i][0] != '_' || words[i][1] != '=')
				ft_print_some(words[i]);
}

void	ft_print_export(t_v *v, int mark, t_ls *data)
{
	int		i;
	int		count;

	i = 0;
	count = ft_lstsize_2(v);
	data->exp.words = (char **)malloc(sizeof(char *) * count);
	if (!data->exp.words)
		ft_error();
	while (v)
	{
		data->exp.words[i] = ft_strdup(v->str);
		if (!data->exp.words[i])
			ft_error();
		i++;
		v = v->next;
	}
	ft_print_export_2(data->exp.words, count, mark);
	i = -1;
	while (data->exp.words[++i])
		free_string(&data->exp.words[i]);
	free_2d_string(&data->exp.words);
}

void	ft_create_env(t_v *v, char *str, t_ls *data)
{
	if (!data) //
		return ; //
	while (v->next)
		v = v->next;
	v->str = ft_strdup(str);
	if (v->str == NULL)
		ft_error();
	v->next = ft_lstnew_2(NULL);
	if (v->next == NULL)
		ft_error();
}

void	ft_export(char **words, t_v *v, int mark, t_ls *data)
{
	int	i;
	int	set;

	set = 0;
	i = 0;
	while (words[++i] || set == 0)
	{
		set = 1;
		if (words[i] == NULL)
		{
			ft_print_export(v, mark, data);
			return ;
		}
		else if (ft_isalpha(words[i][0])
				&& ft_check_export(words[i]) == 0 && data->c_e[i] == 'a')
			ft_create_env(v, words[i], data);
		else if (!ft_isalpha(words[i][0]) || ft_check_export(words[i]) != 0)
		{
			ft_printf_fd(2,
				"minishell: export: `%s': not a valid identifier\n", words[i]);
			data->statuscode = 400;
		}
	}
	free_string(&data->c_e);
}
