/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:10:07 by zmin              #+#    #+#             */
/*   Updated: 2025/11/12 21:56:23 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globals.h"
#include "lexer.h"
#include "utils.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

static char	*get_var_value(char *var_name, char **envp)
{
	int	i;
	int	len;

	if (!var_name || !*var_name)
		return (ft_strdup(""));
	if (!ft_strcmp(var_name, "?"))
		return (ft_itoa(g_status));
	i = 0;
	len = ft_strlen(var_name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var_name, len) && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

static char	*expand_var(char *s, int *i, char **envp)
{
	int		start;
	char	*var_name;
	char	*var_value;

	(*i)++;
	if (!s[*i] || (!ft_isalnum(s[*i]) && s[*i] != '_' && s[*i] != '?'))
		return (ft_strdup("$"));
	start = *i;
	if (s[*i] == '?')
		(*i)++;
	else
		while (s[*i] && ft_validvarchar(s[*i]))
			(*i)++;
	var_name = ft_substr(s, start, *i - start);
	var_value = get_var_value(var_name, envp);
	free(var_name);
	return (var_value);
}

char	*lexer_expand_var(char *token, char **envp)
{
	int		i;
	int		in_single_quote;
	char	*res;
	char	*expanded_var;

	i = 0;
	in_single_quote = 0;
	res = ft_strdup("");
	while (token && token[i])
	{
		if (token[i] == '\'' && !in_single_quote)
			in_single_quote = 1;
		else if (token[i] == '\'' && in_single_quote)
			in_single_quote = 0;
		if (token[i] == '$' && !in_single_quote)
		{
			expanded_var = expand_var(token, &i, envp);
			res = join_and_free(res, expanded_var);
			continue ;
		}
		res = ft_appendchar(res, token[i]);
		i++;
	}
	free(token);
	return (res);
}
