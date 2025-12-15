/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayminmaw <zayminmaw@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:47:10 by zmin              #+#    #+#             */
/*   Updated: 2025/12/15 11:33:48 by zayminmaw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

// 
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
		ft_syntax_error(QUOTE_ERR, 1);
		return (ft_strarr_free(*tokens), 3);
	}
	i = 0;
	while ((*tokens)[i])
	{
		(*tokens)[i] = lexer_expand_var((*tokens)[i], env->envp);
		i++;
	}
	return (0);
}
