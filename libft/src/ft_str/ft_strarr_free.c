/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:05:55 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:36:29 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Frees a null-terminated array of strings.
** 
** Parameters:
**   str_arr - Array of strings to free (null-terminated array)
** 
** Return:
**   None (void function)
** 
** Edge cases:
**   - Does nothing if str_arr is NULL
**   - Frees each string in the array individually
**   - Frees the array itself after freeing all strings
**   - Assumes array is null-terminated
**   - Useful for cleaning up results from ft_split
*/
void	ft_strarr_free(char **str_arr)
{
	int	i;

	i = 0;
	if (!str_arr)
		return ;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}
