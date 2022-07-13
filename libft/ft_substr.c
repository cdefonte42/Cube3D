/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:34:01 by cdefonte          #+#    #+#             */
/*   Updated: 2022/01/25 10:20:31 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Alloue et retourne une chaine de caracteres issue de la chaine 's'. 
//Cette nouvelle chaine commence a l'index 'start' 
//et a pour taille maximale 'len'.
//Retours: la nouvelle chaine de caracteres. NULL si l'allocation echoue.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*result;

	i = 0;
	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (len > slen - start)
		len = slen - start;
	while (start < slen && s[start + i] && i < len)
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (start < slen && i < len && s[i])
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
