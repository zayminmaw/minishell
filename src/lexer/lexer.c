/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:47:10 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 18:01:30 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "parser.h"

// main lexer: pad input, split into tokens, check quotes and expand vars
// returns 0 on success
// returns 1 if padding failed
// returns 2 if tokenization failed
// returns 3 if unmatched quotes (prints syntax error)
int	lexer(char *input, t_env *env, char ***tokens)
{
	int	i;

	input = lexer_pad_str(input);
	if (!input)
		return (1);
	*tokens = lexer_tokenize(input);
	free(input);
	if (!(*tokens))
		return (2);
	if (lexer_check_quote(*tokens))
	{
		ft_syntax_error(QUOTE_ERR, 2);
		return (ft_strarr_free(*tokens), 3);
	}
	i = 0;
	while ((*tokens)[i])
	{
		(*tokens)[i] = lexer_expand_var((*tokens)[i], env->envp);
		i++;
	}
	*tokens = expand_wildcards(*tokens);
	if (!(*tokens))
		return (2);
	return (0);
}
