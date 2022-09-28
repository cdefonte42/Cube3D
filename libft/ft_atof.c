/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraets <mbraets@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:18:11 by mbraets           #+#    #+#             */
/*   Updated: 2022/09/27 23:54:27 by mbraets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	double	decimal(const char *s, int i)
{
	double	fractional;
	int		len;

	fractional = 0;
	len = ft_strlen(s) - 1;
	while (!ft_isdigit(s[len]))
		len--;
	while (len != i - 1)
	{
		fractional += s[len] - '0';
		fractional /= 10;
		len--;
	}
	return (fractional);
}

/*
 *   Skip les premiers - et + mais regarde seulement
 *    le premier char pour la negation !
 */
double	ft_atof(const char *s)
{
	double	res;
	int		i;
	int		neg;

	i = 0;
	res = 0;
	neg = 1;
	if (s[0] == '-')
		neg = -1;
	while (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
	{
		res *= 10;
		res += s[i] - '0';
		i++;
	}
	if (s[i++] != '.')
		return (res * neg);
	if (s[i] == '\0' || !ft_isdigit(s[i]))
		return (res * neg);
	res += decimal(s, i);
	return (res * neg);
}
