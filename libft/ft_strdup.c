/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:37:54 by cdefonte          #+#    #+#             */
/*   Updated: 2022/02/05 16:07:47 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	int		i;
	int		slen;

	slen = 0;
	i = 0;
	while (s[slen])
		slen++;
	cpy = malloc(sizeof(char) * (slen + 1));
	if (!cpy)
		return (NULL);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	size;
	size_t	i;
	char	*s2;

	if (s1 == NULL)
		return (NULL);
	size = ft_strlen(s1);
	s2 = ft_calloc(size, sizeof(char) + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (i < n && i < size)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
