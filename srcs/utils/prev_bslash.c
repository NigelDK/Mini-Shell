/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prev_bslash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-koni <nde-koni@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:25:51 by nde-koni          #+#    #+#             */
/*   Updated: 2021/04/16 19:27:40 by nde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		prev_bslash(char *s, int k, int q)
{
	int	i;

	i = 0;
	if (s[k] == ' ' || q == 1)
		return (0); // protection for space
	while (--k >= 0 && s[k] == '\\')
		i++;
	return (i % 2);
}
