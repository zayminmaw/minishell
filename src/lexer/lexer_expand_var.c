/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayminmaw <zayminmaw@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:10:07 by zmin              #+#    #+#             */
/*   Updated: 2025/12/27 13:28:42 by zayminmaw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "lexer.h"
#include "utils.h"

// handle quote toggle
// track both single and double quotes
// single quotes disable expansion, double quotes don't
static void	handle_quote(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
	{
		if (*in_single_quote)
			*in_single_quote = 0;
		else
			*in_single_quote = 1;
	}
	else if (c == '"' && !(*in_single_quote))
	{
		if (*in_double_quote)
			*in_double_quote = 0;
		else
			*in_double_quote = 1;
	}
}

// allocate empty string res
// iterate the tokens
// do nothing if in single quote
// else expand var and add it to res
// if it's not a var add it as a normal char
// after loop is done free old token
// return res as new token
char	*lexer_expand_var(char *token, char **envp)
{
	int		i;
	int		in_single_quote;
	int		in_double_quote;
	char	*res;
	char	*expanded_var;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (token && token[i])
	{
		handle_quote(token[i], &in_single_quote, &in_double_quote);
		if (token[i] == '$' && !in_single_quote)
		{
			expanded_var = expand_var(token, &i, envp);
			res = join_and_free(res, expanded_var);
			continue ;
		}
		res = ft_appendchar(res, token[i]);
		i++;
	}
	free(token);
	return (res);
}
