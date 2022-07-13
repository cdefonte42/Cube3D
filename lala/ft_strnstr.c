/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:15:23 by cdefonte          #+#    #+#             */
/*   Updated: 2021/11/30 12:37:02 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (!little[0])
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		k = i;
		ptr = (char *)big + i;
		while (big[k] == little[j] && big[k] && k < len)
		{
			k++;
			j++;
			if (little[j] == 0)
				return (ptr);
		}
		i++;
	}
	return (NULL);
}
