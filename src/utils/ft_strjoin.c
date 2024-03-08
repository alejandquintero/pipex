/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:59:56 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/08 19:01:17 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	char	aux[1];
	char	*s3;
	int		i;
	int		j;

	if (!s1)
	{
		aux[0] = '\0';
		s1 = aux;
	}
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = malloc(total_len * sizeof(char));
	if (!s3)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		s3[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		s3[i + j] = s2[j];
	s3[i + j] = '\0';
	return (s3);
}
