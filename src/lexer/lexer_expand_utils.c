/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:43:38 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 20:47:37 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "lexer.h"
#include "utils.h"

// join two string from param
// free 2 param
// return new malloc string
char	*join_and_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

// if var name empty return empty string
// if ? return exit status
// interate the envp and compare
// return the value by shifting the pointer to value
// if not found return empty
char	*get_var_value(char *var_name, char **envp)
{
	int	i;
	int	len;

	if (!var_name || !*var_name)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(get_exit_status()));
	if (!envp)
		return (ft_strdup(""));
	i = 0;
	len = ft_strlen(var_name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

// increment i to pass $
// if the var name is not valid return $
// get start
// if s[*i] is just ? increment one time
// else interate until not valid var name
// get var name from start to *i - start
// get var value
// free var name as it has no more use
char	*expand_var(char *s, int *i, char **envp)
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
