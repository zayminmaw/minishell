/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:45:57 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/15 20:16:50 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "minishell.h"
#include "prompt.h"
#include "utils.h"
#include <fcntl.h>
#include <lexer.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

static void	set_heredoc_child_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	set_parent_wait_signals(struct sigaction *old_int,
		struct sigaction *old_quit)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, old_int);
	sigaction(SIGQUIT, &sa, old_quit);
}

static void	restore_parent_signals(struct sigaction *old_int,
		struct sigaction *old_quit)
{
	sigaction(SIGINT, old_int, NULL);
	sigaction(SIGQUIT, old_quit, NULL);
}

static void	read_heredoc_lines(int fd, char *delimiter, char **envp)
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

int	write_heredoc(t_node *node)
{
	pid_t				pid;
	int					status;
	int					fd;
	struct sigaction	old_int;
	struct sigaction	old_quit;

	if (node->in_flag != 2)
		return (0);
	pid = fork();
	if (pid < 0)
		return (ft_process_error(FORK_ERR, 1), 0);
	if (pid == 0)
	{
		set_heredoc_child_signals();
		fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			exit(1);
		read_heredoc_lines(fd, node->delimiter, node->env->envp);
		close(fd);
		exit(0);
	}
	set_parent_wait_signals(&old_int, &old_quit);
	if (waitpid(pid, &status, 0) == -1)
	{
		restore_parent_signals(&old_int, &old_quit);
		unlink(".tmp");
		set_exit_status(1);
		return (1);
	}
	restore_parent_signals(&old_int, &old_quit);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(".tmp");
		write(STDOUT_FILENO, "\n", 1);
		set_exit_status(130);
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink(".tmp");
		set_exit_status(WEXITSTATUS(status));
		return (1);
	}
	return (0);
}
