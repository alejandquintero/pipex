/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:08:09 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/08 22:09:29 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	open_files(t_pipex *p, char *argv[])
{
	p->input = open(argv[1], O_RDONLY);
	if (p->input == ERROR)
		perror_and_free(ERROR_INFILE, p);
	p->output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->output == ERROR)
		perror_and_free(ERROR_OUTFILE, p);
}

void	close_files(t_pipex *p)
{
	close(p->input);
	close(p->output);
}

void	close_pipes(t_pipex *p)
{
	close(p->pipe[0]);
	close(p->pipe[1]);
}
