/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:47:10 by zmin              #+#    #+#             */
/*   Updated: 2025/11/07 21:17:32 by zmin             ###   ########.fr       */
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
	free(input);
	if (!(*token))
		return (2);
	return (0);
}
