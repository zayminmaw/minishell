/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:45:57 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/10 17:31:57 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <fcntl.h>
#include <lexer.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

static void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	read_heredoc_lines(int fd, char *delimiter, char **envp)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expanded = lexer_expand_var(line, envp);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
}

void	write_heredoc(t_node *node)
{
	int	fd;

	if (node->in_flag != 2)
		return ;
	set_heredoc_signals();
	fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	read_heredoc_lines(fd, node->delimiter, node->env->envp);
	close(fd);
}
