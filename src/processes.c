/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:30:40 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/02 18:48:13 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

// char	**get_command(t_pipex *p)
// {
// 	(void)p;
// 	char *command[] = {"/bin/ls", "-la", NULL};
// 	return (command);
// }

void	process1(t_pipex *p)
{
	int	fd;	
	char *command[] = {"/bin/cat", "-e", NULL};
	
	fd = open(p->input, O_RDONLY);
	if (fd == ERROR)
		perror_and_free("Error al abrir el infile", p);
	dup2(fd, STDIN_FILENO);
	dup2(p->fd[1], STDOUT_FILENO);
	close(p->fd[0]);
	close(p->fd[1]);
	close(fd);
	// command = get_command(p);
	execve(command[0], command, NULL);	
}

void	process2(t_pipex *p)
{
	char *command[] = {"/usr/bin/grep", "pipe", NULL};
	int fd;

	fd = open(p->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == ERROR)
		perror_and_free("Error al crear el archivo de salida", p);
	dup2(p->fd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(p->fd[0]);
	close(p->fd[1]);
	close(fd);
	execve(command[0], command, NULL);
}