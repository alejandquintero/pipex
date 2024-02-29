/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:01:36 by aquinter          #+#    #+#             */
/*   Updated: 2024/02/29 22:28:02 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

static size_t	len_word(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static size_t	words(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			i += len_word((s + i), c);
			j++;
		}
		else
			i++;
	}
	return (j);
}

static void	free_memory(void **mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(mem[i]);
		i++;
	}
	free(mem);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	char	**strs;

	strs = ft_calloc(words(s, c) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	j = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			strs[j] = ft_calloc(len_word(s, c) + 1, sizeof(char));
			if (!strs[j])
			{
				free_memory((void **)strs, j);
				return (NULL);
			}
			ft_strlcpy(strs[j], s, len_word(s, c) + 1);
			s += len_word(s, c);
			j++;
		}
		else
			s++;
	}
	return (strs);
}
