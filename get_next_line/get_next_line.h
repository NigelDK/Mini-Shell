/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minummin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:56:42 by minummin          #+#    #+#             */
/*   Updated: 2020/11/28 16:57:39 by minummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int     ft_strchr(char *s);
int     ft_strlen(char *s);
int     ft_free(char **s);
void    *ft_memmove(char *dest, char *src, int len);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_get_line(char *s);
char    *ft_get_rest(char *s);
int     get_next_line(int fd, char **line);

#endif
