/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 23:09:00 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:32:39 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Deletes and frees all nodes in a linked list.
** 
** Parameters:
**   lst - Pointer to the first node of the list
**   del - Function to delete the content of each node
** 
** Return:
**   None (void function)
** 
** Edge cases:
**   - Sets *lst to NULL after clearing
**   - Uses ft_lstdelone to delete each node
**   - del function is called on each node's content
**   - Safe to call on empty list
**   - Undefined behavior if del is NULL (no null check)
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	free(*lst);
	*lst = NULL;
}
