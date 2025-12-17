/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:45:57 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/15 21:50:09 by wmin-kha         ###   ########.fr       */
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

static char	*heredoc_tmpname(int idx)
{
	char	*num;
	char	*name;

	num = ft_itoa(idx);
	if (!num)
		return (NULL);
	name = ft_strjoin("/tmp/heredoc_", num);
	free(num);
	return (name);
}

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

static void	read_heredoc_lines(int fd, char **delimiter, char **envp)
{
	char	*line;
	char	*expanded;
	int		di;
	int		should_write;

	di = 0;
	while (delimiter && delimiter[di])
	{
		should_write = (delimiter[di + 1] == NULL);
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (ft_strcmp(line, delimiter[di]) == 0)
			{
				free(line);
				break ;
			}
			if (should_write)
			{
				expanded = lexer_expand_var(line, envp);
				write(fd, expanded, ft_strlen(expanded));
				write(fd, "\n", 1);
				free(expanded);
			}
		}
		di++;
	}
}

int	write_heredoc(t_node *node, int idx)
{
	pid_t				pid;
	int					status;
	int					fd;
	struct sigaction	old_int;
	struct sigaction	old_quit;
	char				*tmp;

	if (node->in_flag != 2)
		return (0);
	if (!node->delimiters || !node->delimiters[0])
	{
		node->in_flag = 0;
		return (0);
	}
	tmp = heredoc_tmpname(idx);
	if (!tmp)
		return (set_exit_status(1), 1);
	if (node->infile)
		free(node->infile);
	node->infile = tmp;
	pid = fork();
	if (pid < 0)
	{
		unlink(node->infile);
		free(node->infile);
		node->infile = NULL;
		return (ft_process_error(FORK_ERR, 1), 0);
	}
	if (pid == 0)
	{
		set_heredoc_child_signals();
		fd = open(node->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			exit(1);
		read_heredoc_lines(fd, node->delimiters, node->env->envp);
		close(fd);
		exit(0);
	}
	set_parent_wait_signals(&old_int, &old_quit);
	if (waitpid(pid, &status, 0) == -1)
	{
		restore_parent_signals(&old_int, &old_quit);
		unlink(node->infile);
		set_exit_status(1);
		return (1);
	}
	restore_parent_signals(&old_int, &old_quit);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(node->infile);
		write(STDOUT_FILENO, "\n", 1);
		set_exit_status(130);
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink(node->infile);
		set_exit_status(WEXITSTATUS(status));
		return (1);
	}
	return (0);
}
