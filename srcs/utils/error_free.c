/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:36:14 by minummin          #+#    #+#             */
/*   Updated: 2021/04/29 11:46:58 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_v(t_v *v)
{
	ft_lstclear_2(&v, ft_memdel);
	ft_printf_fd(2, "Error: %s\n", strerror(errno));
	if (errno == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	ft_error_syscall(t_ls *data, t_v **v, char **path, char *temp)
{
	data->i = -1;
	while (path[++data->i])
		free(path[data->i]);
	free(path);
	data->i = -1;
	while (data->words[++data->i])
		free(data->words[data->i]);
	if (data->words)
		free(data->words);
	data->i = -1;
	while (data->words2[++data->i])
		free(data->words2[data->i]);
	if (data->words2)
		free(data->words2);
	if (data->line)
		free(data->line);
	if (temp)
		free(temp);
	ft_lstclear_2(v, ft_memdel);
	ft_printf_fd(2, "Error: %s\n", strerror(errno));
	if (errno == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	ft_error_data_v_2(t_ls *data, t_v **v)
{
	int	i;

	i = -1;
	while (data->words[++i])
		free(data->words[i]);
	if (data->words)
		free(data->words);
	i = -1;
	while (data->words2[++i])
		free(data->words2[i]);
	if (data->words2)
		free(data->words2);
	if (data->line)
		free(data->line);
	ft_lstclear_2(v, ft_memdel);
	ft_printf_fd(2, "Error: %s\n", strerror(errno));
	if (errno == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	ft_error_data_v_child(t_ls *data, t_v **v)
{
	int	i;

	i = -1;
	while (data->words[++i])
		free(data->words[i]);
	if (data->words)
		free(data->words);
	i = -1;
	while (data->words2[++i])
		free(data->words2[i]);
	if (data->words2)
		free(data->words2);
	if (data->line)
		free(data->line);
	ft_lstclear_2(v, ft_memdel);
}

void	ft_error_data_v(t_ls *data, t_v *v)
{
	int	i;

	i = -1;
	while (data->words[++i])
		free(data->words[i]);
	if (data->words)
		free(data->words);
	if (data->line)
		free(data->line);
	ft_lstclear_2(&v, ft_memdel);
	ft_printf_fd(2, "Error: %s\n", strerror(errno));
	if (errno == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
