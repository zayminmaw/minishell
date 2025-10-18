/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:36:56 by zmin              #+#    #+#             */
/*   Updated: 2025/10/02 20:14:43 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_malloc_clear(void)
{
	t_list	**malloc_lst;

	malloc_lst = ft_malloc_lst();
	ft_lstclear(malloc_lst, &free);
}
