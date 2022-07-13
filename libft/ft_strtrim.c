/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:18:46 by cdefonte          #+#    #+#             */
/*   Updated: 2021/12/08 11:27:10 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_fail(void)
{
	char	*s;

	s = malloc(sizeof(char) * 1);
	if (!s)
		return (NULL);
	s[0] = '\0';
	return (s);
}

unsigned int	ft_findstart(char const *s, char const *set)
{
	unsigned int	start;

	start = 0;
	while (s[start] && ft_isset(set, s[start]))
		start++;
	return (start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	end;
	unsigned int	start;
	char			*trimmed;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	start = ft_findstart(s1, set);
	if (start == ft_strlen(s1))
		return (ft_fail());
	end = ft_strlen(s1) - 1;
	while (end != start && ft_isset(set, s1[end]))
		end--;
	trimmed = malloc(sizeof(char) * (end - start + 2));
	if (!trimmed)
		return (NULL);
	while (i <= (end - start))
	{
		trimmed[i] = s1[start + i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
