/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:56:42 by minummin          #+#    #+#             */
/*   Updated: 2021/04/22 15:16:00 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*ft_get_line(char *s);
char	*ft_get_rest(char *s);
int		ft_return(char **s, int ret);
int		ft_free(char **s);
int		get_next_line(int fd, char **line);

#endif
