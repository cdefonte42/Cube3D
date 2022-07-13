/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdefonte <cdefonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:23:38 by cdefonte          #+#    #+#             */
/*   Updated: 2021/12/02 17:42:56 by cdefonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = lst;
	if (!del)
	{
		while (tmp)
		{
			f(tmp->content);
			tmp = tmp->next;
		}
	}
	else
		del(tmp->content);
	return (tmp);
}
