/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:15:31 by cdefonte          #+#    #+#             */
/*   Updated: 2022/02/05 16:07:35 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Alloue et retourne un tableau de chaines de caracteres obtenu en
//seprarent 's' a l'aide du caractere 'c'. 
//Le tableau doit etre termine par NULL.

static char	*ft_strndup(char const *s, size_t size)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(sizeof(char) * size);
	if (!ptr)
		return (NULL);
	while (s[i] && i < (int)size - 1)
	{
		ptr[i] = ((char *)s)[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static void	ft_fail(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab[i] = NULL;
}

static int	ft_nbstr(char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i])
			n++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (n);
}

static char	**lines(char const *s, char c, char **split)
{
	int	k;
	int	j;
	int	i;

	k = 0;
	i = 0;
	while (s[i] && k < ft_nbstr((char *)s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		split[k] = ft_strndup(s + i, j + 1);
		if (!split[k])
		{
			ft_fail(split, k);
			return (NULL);
		}
		i = i + j;
		k++;
	}
	split[k] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = malloc((ft_nbstr((char *)s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	if (ft_nbstr((char *)s, c) == 0)
		split[0] = NULL;
	split = lines(s, c, split);
	if (!split)
		return (NULL);
	return (split);
}
