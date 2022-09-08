/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:13:03 by mbraets           #+#    #+#             */
/*   Updated: 2022/03/22 11:25:21 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlchr(char c, const char *set)
{
	int	i;

	i = -1;
	while (set[++i] != '\0')
		if (set[i] == c)
			return (1);
	return (0);
}

/**
 * @brief Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.
 * @param s1 The string to be trimmed.
 * @param set The reference set of characters to trim.
à la liste.
 * @return The trimmed string.
NULL if the allocation fails.
 */
char	*ft_strtrim_free(char *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	result = NULL;
	if (s1 && set)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strlchr(s1[start], set))
			start++;
		while (end > start && ft_strlchr(s1[end - 1], set))
			end--;
		result = malloc(sizeof(char) * (end - start + 1));
		if (!result)
			return (free((char *)s1), NULL);
		ft_strlcpy(result, s1 + start, end - start + 1);
	}
	free((char *)s1);
	return (result);
}