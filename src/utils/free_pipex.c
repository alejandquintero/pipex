/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:06:42 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/05 22:35:48 by aquinter         ###   ########.fr       */
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
		if (p->cmd_args)
			free_matrix((void **)p->cmd_args);
		if (p->path)
			free_matrix((void **)p->path);
		free(p);
	}
}

void	print(char *s)
{
	write(1, s, ft_strlen(s));
}

void	print_and_free(char *s, t_pipex *p)
{
	free_pipex(p);
	print(s);
	exit(1);
}

void	perror_and_free(char *s, t_pipex *p)
{
	free_pipex(p);
	perror(s);
	exit(1);
}
