/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:27:38 by zmin              #+#    #+#             */
/*   Updated: 2025/11/04 19:25:35 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "utils.h"
#include "lexer.h"

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
			if (lexer(input, env) == 4)
			{
				free(input);
				break ;
			}
		}
		free(input);
	}
	free(prompt);
}
