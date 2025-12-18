/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:17:38 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 20:26:27 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "prompt.h"
#include "utils.h"
#include "validation.h"

// filter out empty tokens (from unexpanded variables like $EMPTY)
// 1. count non-empty tokens
// 2. allocate new array for filtered tokens
// 3. copy only non-empty tokens to new array
// 4. return filtered array
char	**filter_empty_tokens(char **tokens)
{
	int		i;
	int		j;
	int		count;
	char	**filtered;

	count = 0;
	i = -1;
	while (tokens[++i])
		if (tokens[i][0] != '\0')
			count++;
	filtered = malloc(sizeof(char *) * (count + 1));
	if (!filtered)
		return (NULL);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (tokens[i][0] != '\0')
			filtered[j++] = tokens[i];
		i++;
	}
	filtered[j] = NULL;
	return (filtered);
}

// clean quotes from all commands in all nodes
// iterate through each node and clean quotes from each command
void	clean_node_quotes(t_node *nodes, int node_len)
{
	int	i;
	int	j;

	i = 0;
	while (i < node_len)
	{
		if (nodes[i].full_cmd)
		{
			j = 0;
			while (nodes[i].full_cmd[j])
			{
				nodes[i].full_cmd[j] = ft_cleanquotes(nodes[i].full_cmd[j]);
				j++;
			}
		}
		i++;
	}
}

// process tokens before execution
// 1. validate redirections syntax
// 2. validate parentheses syntax
// 3. filter out empty tokens
// 4. parse tokens into nodes
// 5. clean quotes from nodes
// return -1 to continue execution, or error code to stop
int	process_tokens(char **tokens, t_node **nodes, t_env *env)
{
	char	**tokens_filtered;

	if (validate_inout(tokens))
		return (ft_strarr_free(tokens), 3);
	if (validate_parens(tokens))
		return (ft_strarr_free(tokens), 2);
	tokens_filtered = filter_empty_tokens(tokens);
	if (!tokens_filtered || !tokens_filtered[0])
	{
		free(tokens_filtered);
		return (ft_strarr_free(tokens), 0);
	}
	*nodes = parser(tokens_filtered, env);
	free(tokens_filtered);
	ft_strarr_free(tokens);
	clean_node_quotes(*nodes, env->node_len);
	return (-1);
}
