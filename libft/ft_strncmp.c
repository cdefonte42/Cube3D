/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:18:46 by cdefonte          #+#    #+#             */
/*   Updated: 2022/02/02 10:38:55 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s2)
		return (-1);
	if ((s1 && s1[i] == 0) || (s2 && s2[i] == 0))
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
		if ((s1[i] == 0 || s2[i] == 0) && i < n)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
