/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:51:06 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:32:31 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Adds a new node to the front of a linked list.
** 
** Parameters:
**   lst - Pointer to the first node of the list
**   new - The new node to add
** 
** Return:
**   None (void function)
** 
** Edge cases:
**   - new becomes the new first node
**   - new->next is set to the old first node
**   - Works correctly even if list is empty
**   - Undefined behavior if new is NULL (no null check)
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
