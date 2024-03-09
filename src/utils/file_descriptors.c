/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:08:09 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/09 11:42:08 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	open_files(t_pipex *p, char *argv[])
{
	p->input = open(argv[1], O_RDONLY);
	p->output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->input == ERROR)
		perror(ERROR_INFILE);
	if (p->output == ERROR)
		perror(ERROR_OUTFILE);
	if (p->input == ERROR || p->output == ERROR)
	{
		close_files(p);
		free_pipex(p);
		exit(EXIT_FAILURE);
	}
}

void	close_files(t_pipex *p)
{
	if (p->input != ERROR)
		close(p->input);
	if (p->output != ERROR)
		close(p->output);
}

void	close_pipes(t_pipex *p)
{
	close(p->pipe[0]);
	close(p->pipe[1]);
}
