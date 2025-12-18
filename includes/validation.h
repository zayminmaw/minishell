/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:09:34 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 20:58:41 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

int		validate_inout(char **str);
int		validate_parens(char **tokens);
void	print_syntax_error(char *token);
int		is_quoted(char *token);
int		is_redir(char *token);
int		is_pipe(char *token);
int		is_logical_op(char *token);
int		is_invalid_op(char *token);
int		validate_redir_next(char **tokens, int i);
int		validate_pipe_logic_next(char **tokens, int i);
int		validate_tokens_loop(char **tokens);

#endif