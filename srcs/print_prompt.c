/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin </var/mail/minummin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:37:15 by minummin          #+#    #+#             */
/*   Updated: 2021/04/03 14:37:18 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_print_prompt_2(void)
{
	printf("😎  ");
	printf("\033[0;31m");
        printf("~ ");
	printf("\033[0m");
	fflush(stdout);
}

void    ft_print_prompt(int cd)
{
	long size;
	char *buf;
	char *ptr;

	size = pathconf(".", _PC_PATH_MAX);
	if (!(buf = (char *)malloc((size_t)size)))
		ft_error();
	ptr = getcwd(buf, (size_t)size);
	if (cd == 0)
		ft_print_prompt_2();
	else if (cd == 1)
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
