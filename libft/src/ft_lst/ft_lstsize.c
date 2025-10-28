/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:58:14 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:33:33 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Counts the number of nodes in a linked list.
** 
** Parameters:
**   lst - The first node of the list
** 
** Return:
**   Returns the number of nodes in the list.
** 
** Edge cases:
**   - Returns 0 for empty list (lst is NULL)
**   - Iterates through entire list counting nodes
**   - Does not modify the list
*/
int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}
