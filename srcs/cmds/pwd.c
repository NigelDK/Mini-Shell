/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:37:29 by minummin          #+#    #+#             */
/*   Updated: 2021/05/03 16:46:49 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_ls *data, t_v **v)
{
	char	*buf;
	char	*ptr;

	if (!data->words2)
		return ;
	buf = (char *)malloc(sizeof(char) * 1025);
	if (!buf)
		ft_error(data, v);
	ft_bzero(buf, 1025);
	ptr = getcwd(buf, 1025);
	printf("%s\n", buf);
	free(ptr);
}
