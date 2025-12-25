/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:27:38 by zmin              #+#    #+#             */
/*   Updated: 2025/12/25 21:40:39 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "prompt.h"
#include "utils.h"
#include "validation.h"
#include <fcntl.h>

// static void	debug_print_fds(char *msg)
// {
// 	int	i;
// 	int	fd_count;

// 	i = 0;
// 	fd_count = 0;
// 	printf("--- Open FDs (%s) ---\n", msg);
// 	while (i < 100) // Checking first 100 is usually enough
// 	{
// 		if (fcntl(i, F_GETFD) != -1)
// 		{
// 			printf("FD: %d\n", i);
// 			fd_count++;
// 		}
// 		i++;
// 	}
// 	printf("Total: %d\n----------------------\n", fd_count);
// }

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
	int		status;
	char	**tokens;
	t_node	*nodes;

	if (lexer(input, env, &tokens))
		return (1);
	if (!tokens[0] || (tokens[0][0] == '\0' && ft_count_tokens(tokens) == 1))
		return (ft_strarr_free(tokens), 0);
	status = process_tokens(tokens, &nodes, env);
	if (status != -1)
		return (status);
	status = executor(nodes);
	ft_freenodes(nodes);
	return (status);
}

// handle user input after readline
// 1. add to history if not empty
// 2. execute clear command if needed
// 3. interpret and run the input
// 4. return 1 if exit status is 4 (to break main loop)
static int	handle_input(char *input, t_env *env)
{
	int	status;

	post_read_actions(input);
	if (ft_strlen(input))
	{
		status = interpret_and_run(input, env);
		if (status == 4)
			return (1);
	}
	return (0);
}

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
		set_prompt_signals();
		input = readline(prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (handle_input(input, env))
		{
			free(input);
			break ;
		}
		free(input);
	}
	free(prompt);
}
