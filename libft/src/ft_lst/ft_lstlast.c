/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:10:50 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:33:11 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the last node of a linked list.
** 
** Parameters:
**   lst - The first node of the list
** 
** Return:
**   Returns a pointer to the last node,
**   or NULL if the list is empty.
** 
** Edge cases:
**   - Returns NULL if lst is NULL
**   - Iterates through the list until finding node with next = NULL
**   - Returns the only node if list has one element
*/
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}
