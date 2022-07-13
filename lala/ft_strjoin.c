/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:53:48 by cdefonte          #+#    #+#             */
/*   Updated: 2022/01/18 15:45:10 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Alloue et retourne new chaine de caracteres,
//concat de s1 et s2, avec s1 prefixe et s2 suffixe.

static char	*ft_cpy(char *res, const char *s1, const char *s2)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	reslen;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	reslen = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (reslen + 1));
	if (!result)
		return (NULL);
	return (ft_cpy(result, s1, s2));
}
