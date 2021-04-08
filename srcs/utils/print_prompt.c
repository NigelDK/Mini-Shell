/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:37:15 by minummin          #+#    #+#             */
/*   Updated: 2021/04/08 21:05:13 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_print_prompt_2(void)
{
	printf("😎  ");
	printf("\033[0;31m");
	printf("~ ");
	printf("\033[0m");
	fflush(stdout);
}

void    ft_print_prompt(t_ls *data, t_v *v)
{
	long size;
	char *buf;
	char *ptr;

	if (data->n_c == 1)
	{
		printf("\033[0;7m%%\033[0m\n");
		data->n_c = 0;
	}
	size = pathconf(".", _PC_PATH_MAX);
	if (!(buf = (char *)malloc((size_t)size)))
		ft_error_v(v);
	ptr = getcwd(buf, (size_t)size);
	if (data->cd == 0)
		ft_print_prompt_2();
	else if (data->cd == 1)
	{
		if (ft_strcmp_2(ptr, "/", 1) == 0)
			ft_print_prompt_2();
		else
		{
			printf("😎  ");
			printf("\033[0;31m");
			printf("%s ", ft_strstr_rev_2(ptr, "/"));
			printf("\033[0m");
			fflush(stdout);
		}
	}
	free(ptr);
}
