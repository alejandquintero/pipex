/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:04:51 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/08 19:15:15 by aquinter         ###   ########.fr       */
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

void	free_pipex(t_pipex *p)
{
	if (p)
	{
		if (p->args)
			free_matrix((void **)p->args);
		if (p->path)
			free_matrix((void **)p->path);
		free(p);
	}
}
