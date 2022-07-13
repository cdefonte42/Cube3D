/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabtablen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:46:15 by cdefonte          #+#    #+#             */
/*   Updated: 2022/01/25 15:26:45 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_tabtablen(char **tab)
{
	size_t	len;

	if (!tab || !*tab)
		return (0);
	len = 0;
	while (tab && tab[len])
		len++;
	return (len);
}
