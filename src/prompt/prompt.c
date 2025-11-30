/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:27:38 by zmin              #+#    #+#             */
/*   Updated: 2025/11/30 19:08:16 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "prompt.h"
#include "utils.h"
#include "validation.h"

static char	*get_prompt(char **envp)
{
	int		i;
	char	*username;
	char	*prompt;

	i = 0;
	username = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "USER=", 5))
		{
			username = ft_strdup(envp[i] + 5);
			break ;
		}
		i++;
	}
	if (!username)
	{
		prompt = ft_strdup("minishell> ");
		return (prompt);
	}
	prompt = ft_strjoin(username, "@minishell> ");
	free(username);
	return (prompt);
}

// save history and csi for move to home and erase screen
static void	post_read_actions(char *input)
{
	if (input[0])
		add_history(input);
	if (!ft_strncmp(input, "clear", 5))
		printf("\033[H\033[2J");
}

int	interpret_and_run(char *input, t_env *env)
{
	int		i;
	char	**tokens;
	t_node	*nodes;

	if (lexer(input, env, &tokens))
		return (1);
	i = 0;
	while (tokens[i])
	{
		tokens[i] = ft_cleanquotes(tokens[i]);
		if (!tokens[i])
			return (ft_strarr_free(tokens), 2);
		i++;
	}
	if (validate_inout(tokens))
		return (ft_strarr_free(tokens), 3);
	nodes = parser(tokens, env);
	executor(nodes);
	ft_freenodes(nodes);
	return (0);
}
// i = 0;
// while (tokens[i])
// {
// 	printf("%s\n", tokens[i]);
// 	i++;
// }

void	prompt(t_env *env)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt(env->envp);
	while (1)
	{
		override_sig();
		input = readline(prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		post_read_actions(input);
		if (ft_strlen(input))
		{
			if (interpret_and_run(input, env) == 4)
			{
				free(input);
				break ;
			}
		}
		free(input);
	}
	free(prompt);
}
