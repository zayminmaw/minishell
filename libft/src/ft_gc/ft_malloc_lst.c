/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:31:53 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:31:13 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns a static pointer to the malloc tracking list.
** 
** Parameters:
**   None
** 
** Return:
**   Returns a pointer to the static malloc tracking list.
** 
** Edge cases:
**   - Uses static variable to persist across calls
**   - Initializes to NULL on first call
**   - Returns pointer to pointer (t_list **) for list manipulation
**   - Used internally by ft_malloc and ft_malloc_clear
*/
t_list	**ft_malloc_lst(void)
{
	static t_list	*malloc_lst;

	malloc_lst = NULL;
	return (&malloc_lst);
}
