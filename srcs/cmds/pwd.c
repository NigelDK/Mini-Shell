/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:37:29 by minummin          #+#    #+#             */
/*   Updated: 2021/04/08 20:59:06 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(char **words)
{
	long size;
	char *buf;
	char *ptr;

	if (words[1])
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	size = pathconf(".", _PC_PATH_MAX);
	if (!(buf = (char *)malloc((size_t)size)))
		ft_error();
	ptr = getcwd(buf, (size_t)size);
	printf("%s\n", ptr);
	free(ptr);
}
