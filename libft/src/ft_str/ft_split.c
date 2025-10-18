/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:21:02 by zmin              #+#    #+#             */
/*   Updated: 2025/08/30 18:21:25 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*make_word(char const *s, char c)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int			i;
	int			word;
	char		**tab;

	if (!s)
		return (NULL);
	word = count_word(s, c);
	tab = (char **)malloc((word + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			tab[i++] = make_word(s, c);
			while (*s && *s != c)
				s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
/*
#include <stdio.h>
 int main(void)
 {
     int              i;
      char    **arr;
      char    *s1;
      char    c;

      i = 0;
      s1 = "The-Devil's-Advocate";
      c = '-';
      printf("%d", count_word(s1, c));
      printf("%s",make_word(s1,c));
     arr = ft_split(s1, c);
     if (!arr)
     {
	     printf("\nGG\n");
         return (1);
     }
      printf("%s\n", s1);
      while (arr[i])
     {
         printf("%s ", arr[i]);
         free(arr[i]);
         i++;
     }
     free(arr);
     return (0);
 }
*/
