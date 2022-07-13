/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:21:35 by cdefonte          #+#    #+#             */
/*   Updated: 2021/12/06 15:20:41 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	void			*ptr;
	int				i;

	i = 0;
	if (n == 0)
		return (NULL);
	src = (unsigned char *)s;
	while (i < (int)n)
	{
		if (src[i] == (unsigned char)c % 256)
		{
			ptr = src + i;
			return (ptr);
		}
		i++;
	}
	if ((unsigned char)c == '\0')
	{
		ptr = src + i;
		return (ptr);
	}
	return (NULL);
}
