/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:47:10 by zmin              #+#    #+#             */
/*   Updated: 2025/11/07 21:01:31 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

int	lexer(char *input, t_env *env, char ***token)
{
	(void)env;
	input = lexer_pad_str(input);
	if (!input)
		return (1);
	*token = lexer_tokenize(input);
	return (0);
}
