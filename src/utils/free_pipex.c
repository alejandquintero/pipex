/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:06:42 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/02 16:44:26 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	free_matrix(void **mem)
{
	int	size;
	int	i;

	size = 0;
	while (mem[size])
		size++;
	i = 0;
	while (i < size)
	{
		free(mem[i]);
		i++;
	}
	free(mem);
}

void	exit_pipex(t_pipex *p)
{
	if (p)
	{
		if (p->path)
			free_matrix((void **)p->path);
		if (p->input)
			free(p->input);
		free(p);
	}
	exit(1);
}

void	print(char *s)
{
	write(1, s, ft_strlen(s));
}

void	print_exit(char *s, t_pipex *p)
{
	print(s);
	exit_pipex(p);
}
