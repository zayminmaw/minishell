/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:33:05 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:32:24 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Adds a new node to the back of a linked list.
** 
** Parameters:
**   lst - Pointer to the first node of the list
**   new - The new node to add
** 
** Return:
**   None (void function)
** 
** Edge cases:
**   - If list is empty (*lst is NULL), new becomes the first node
**   - Uses ft_lstlast to find the last node
**   - Undefined behavior if new is NULL (no null check)
*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}
