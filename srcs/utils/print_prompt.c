/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:37:15 by minummin          #+#    #+#             */
/*   Updated: 2021/04/23 19:57:13 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_prompt_3(int statuscode)
{
	long	size;
	char	*buf;
	char	*ptr;

	statuscode = 1;
	size = pathconf(".", _PC_PATH_MAX);
	buf = (char *)malloc((size_t)size);
	if (!buf)
		ft_error();
	ptr = getcwd(buf, (size_t)size);
	if (ft_strcmp_2(ptr, getenv("HOME"), 1) == 0)
		ft_print_prompt_2(statuscode);
	else
	{
		if (statuscode == 0)
			printf("😎  \033[0;32m");
		else
			printf("😡  \033[0;31m");
		if (ft_strcmp_2(ptr, "/", 1) == 0)
			printf("/ ");
		else
			printf("%s ", ft_strstr_rev_2(ptr, "/"));
		printf("\033[0m");
		fflush(stdout);
	}
	free(ptr);
}

void	ft_print_prompt_2(int statuscode)
{
	if (statuscode == 0)
		printf("😎  \033[0;32m");
	else
		printf("😡  \033[0;31m");
	printf("~ ");
	printf("\033[0m");
	fflush(stdout);
}

char	*ft_prompt_2(t_v *v)
{
	long	size;
	char	*buf;

	size = pathconf(".", _PC_PATH_MAX);
	buf = (char *)malloc((size_t)size);
	if (!buf)
		ft_error_v(v);
	return (getcwd(buf, (size_t)size));
}

void	ft_print_prompt(t_ls *data, t_v *v)
{
	char	*ptr;

	ptr = ft_prompt_2(v);
	if (data->cd == 0 || data->cd == 2)
		ft_print_prompt_2(data->statuscode);
	else if (data->cd == 1)
	{
		if (ft_strcmp_2(ptr, getenv("HOME"), 1) == 0)
			ft_print_prompt_2(data->statuscode);
		else
		{
			if (data->statuscode == 0)
				printf("😎  \033[0;32m");
			else
				printf("😡  \033[0;31m");
			if (ft_strcmp_2(ptr, "/", 1) == 0)
				printf("/ ");
			else
				printf("%s ", ft_strstr_rev_2(ptr, "/"));
			printf("\033[0m");
			fflush(stdout);
		}
	}
	free(ptr);
}
