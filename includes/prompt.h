/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:15:12 by zmin              #+#    #+#             */
/*   Updated: 2025/12/10 17:24:32 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/ioctl.h>

void	prompt(t_env *env);
void	set_prompt_signals(void);
void	set_execution_signals(void);
void	set_child_signals(void);

#endif