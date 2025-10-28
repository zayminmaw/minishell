/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:36:56 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:29:59 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Frees all memory tracked by ft_malloc.
** 
** Parameters:
**   None
** 
** Return:
**   None (void function)
** 
** Edge cases:
**   - Gets the malloc tracking list from ft_malloc_lst
**   - Uses ft_lstclear to free all tracked allocations
**   - Uses free as the deletion function
**   - Should be called at program end to avoid memory leaks
**   - Safe to call even if no allocations were made
*/
void	ft_malloc_clear(void)
{
	t_list	**malloc_lst;

	malloc_lst = ft_malloc_lst();
	ft_lstclear(malloc_lst, &free);
}
