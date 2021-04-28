/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:37:15 by minummin          #+#    #+#             */
/*   Updated: 2021/04/28 15:24:31 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_prompt_3(int statuscode)
{
	char	*buf;
	char	*ptr;

	statuscode = 1;
	buf = (char *)malloc(sizeof(char) * 1025);
	if (!buf)
		ft_error();
	ft_bzero(buf, 1025);
	ptr = getcwd(buf, 1025);
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
	char	*buf;

	buf = (char *)malloc(sizeof(char) * 1025);
	if (!buf)
		ft_error_v(v);
	ft_bzero(buf, 1025);
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
