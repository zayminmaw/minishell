/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:58:40 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:32:56 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Deletes and frees a single node from a linked list.
** 
** Parameters:
**   lst - The node to delete
**   del - Function to delete the content of the node
** 
** Return:
**   None (void function)
** 
** Edge cases:
**   - Calls del on the node's content before freeing the node
**   - Does not unlink the node from the list (caller's responsibility)
**   - Undefined behavior if lst or del is NULL (no null check)
**   - Does not set next pointer to NULL
*/
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}
