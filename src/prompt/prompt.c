/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:27:38 by zmin              #+#    #+#             */
/*   Updated: 2025/12/10 19:27:51 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "prompt.h"
#include "utils.h"
#include "validation.h"

// get prompt when username is not avaliable
// only minishell> will be displayed
// if username is avaliable will show username@minishell>
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

// 1. Lexer (tokenize)
// 2. clean/remove quotes (clean quotes from token)
// 3. validate if redir are syntactically correct
// 4. parser (parse token into nodes)
// 5. execute
int	interpret_and_run(char *input, t_env *env)
{
	int		i;
	int		status;
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
	if (validate_parens(tokens))
		return (ft_strarr_free(tokens), 2);
	nodes = parser(tokens, env);
	ft_strarr_free(tokens);
	status = executor(nodes);
	ft_freenodes(nodes);
	return (status);
}
// i = 0;
// while (tokens[i])
// {
// 	printf("%s\n", tokens[i]);
// 	i++;
// }

// where what user type in will come in here
// 1. first get prompt
// 2. readline if the input is EOF exit
// 3. add to history
// 4. then interpret and run
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
