/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:31:53 by zmin              #+#    #+#             */
/*   Updated: 2025/10/02 20:14:33 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**ft_malloc_lst(void)
{
	static t_list	*malloc_lst;

	malloc_lst = NULL;
	return (&malloc_lst);
}
