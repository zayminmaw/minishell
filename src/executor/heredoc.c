/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:45:57 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/24 21:27:17 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "executor.h"
#include "minishell.h"
#include "prompt.h"
#include "utils.h"
#include <errno.h>
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

static void	read_heredoc_lines(int fd, char *delimiter, char **envp)
{
	char	*line;
	char	*expanded;

	if (!delimiter)
		return ;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (!line)
				write_eof_warning(delimiter);
			else
				free(line);
			break ;
		}
		expanded = lexer_expand_var(line, envp);
		if (expanded)
		{
			write(fd, expanded, ft_strlen(expanded));
			write(fd, "\n", 1);
			free(expanded);
		}
	}
}

static pid_t	fork_heredoc_child(char *tmp, char *delimiter, char **envp)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		set_heredoc_child_signals();
		fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			exit(1);
		read_heredoc_lines(fd, delimiter, envp);
		close(fd);
		exit(0);
	}
	return (pid);
}

static int	wait_heredoc_child(pid_t pid, char *tmp)
{
	int					status;
	struct sigaction	sa;
	struct sigaction	old_int;
	struct sigaction	old_quit;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, &old_int);
	sigaction(SIGQUIT, &sa, &old_quit);
	while (waitpid(pid, &status, 0) == -1 && errno == EINTR)
		;
	sigaction(SIGINT, &old_int, NULL);
	sigaction(SIGQUIT, &old_quit, NULL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (unlink(tmp), write(1, "\n", 1), set_exit_status(130), 1);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (unlink(tmp), set_exit_status(WEXITSTATUS(status)), 1);
	return (0);
}

int	write_heredoc(t_node *node, int idx)
{
	pid_t	pid;
	char	*tmp;
	char	*delimiter;

	if (node->in_flag != 2)
		return (0);
	delimiter = get_last_delimiter(node);
	if (!delimiter)
		return (node->in_flag = 0, 0);
	tmp = heredoc_tmpname(idx);
	if (!tmp)
		return (set_exit_status(1), 1);
	pid = fork_heredoc_child(tmp, delimiter, node->env->envp);
	if (pid < 0)
		return (free(tmp), ft_process_error(FORK_ERR, 1), 0);
	if (wait_heredoc_child(pid, tmp))
		return (free(tmp), 1);
	free_infiles(node);
	return (set_heredoc_infile(node, tmp));
}
