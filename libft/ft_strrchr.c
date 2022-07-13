/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:17:50 by cdefonte          #+#    #+#             */
/*   Updated: 2022/02/23 12:57:05 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)s;
	while (s && s[i])
		i++;
	if (c % 256 == '\0')
		return (ptr + i);
	while (i > 0)
	{
		if (s[i - 1] == c % 256)
			return (ptr + i - 1);
		i--;
	}
	return (NULL);
}
