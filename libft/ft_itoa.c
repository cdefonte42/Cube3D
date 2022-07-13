/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:48:35 by cdefonte          #+#    #+#             */
/*   Updated: 2021/12/07 17:23:45 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbnum(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0 || n == 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_fill(int n, int i, char *result)
{
	int	sign;

	sign = 1;
	if (n < 0)
	{
		n = -n;
		result[0] = '-';
		sign = -1;
	}
	while ((i >= 0 && sign == 1) || i > 0)
	{
		result[i] = n % 10 + 48;
		i--;
		n = n / 10;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;

	i = nbnum(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	result[i] = '\0';
	i--;
	return (ft_fill(n, i, result));
}
