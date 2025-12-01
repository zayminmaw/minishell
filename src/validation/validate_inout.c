/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_inout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:03:52 by zmin              #+#    #+#             */
/*   Updated: 2025/12/01 18:35:29 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "validation.h"

// return 0 if valid and 1 if not. 
// validate if redir are followed by actural params
int	validate_inout(char **str)
{
	int	saw_redir;

	saw_redir = 0;
	while (*str)
	{
		if (!ft_strncmp(*str, ">>", 3) || !ft_strncmp(*str, "<<", 3)
			|| !ft_strncmp(*str, ">", 2) || !ft_strncmp(*str, "<", 2))
		{
			if (saw_redir)
				return (ft_syntax_error(SYN_ERR, 1), 1);
			saw_redir = 1;
		}
		else
			saw_redir = 0;
		str++;
	}
	return (0);
}
