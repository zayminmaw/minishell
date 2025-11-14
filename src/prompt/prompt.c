/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:27:38 by zmin              #+#    #+#             */
/*   Updated: 2025/11/14 19:53:38 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "prompt.h"
#include "utils.h"

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
		prompt = ft_strdup("minishell>");
		return (prompt);
	}
	prompt = ft_strjoin(username, "@minishell>");
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

	(void)nodes;
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
	return (0);
}

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
			if (interpret_and_run(input, env) == 3)
			{
				free(input);
				break ;
			}
		}
		free(input);
	}
	free(prompt);
}
