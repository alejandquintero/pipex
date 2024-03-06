/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:30:40 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/06 20:17:31 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*build_path_cmd(char *path, char **args)
{
	char	*aux;
	char	*command;

	aux = ft_strjoin(path, "/");
	if (!aux)
	{
		print("Error al crear comando\n");
		return (NULL);	
	}
	command = ft_strjoin(aux, args[0]);
	free(aux);
	if (!command)
		return (NULL);
	return (command);
}

int	execute(t_pipex *p, char *command)
{
	int	i;

	i = 0;
	p->cmd_args = ft_split(command, ' ');
	if (!p->cmd_args)
		print_and_free("Error al crear argumentos\n", p);
	while (p->path[i])
	{
		p->cmd = build_path_cmd(p->path[i], p->cmd_args);
		if (!p->cmd)
			print_and_free("Error al construir comando", p);
		if (access(p->cmd, X_OK) == SUCCESS)
			execve(p->cmd, p->cmd_args, p->envp);
		free(p->cmd);
		i++;
	}
	write(STDERR_FILENO, "pipex: command not found: ", 26);
	write(STDERR_FILENO, p->cmd_args[0], ft_strlen(p->cmd_args[0]));
	return (ERROR);
}

void	process1(t_pipex *p)
{
	int		fd_in;
	int		fd_out;

	fd_in = open(p->input, O_RDONLY);
	if (fd_in == ERROR)
		perror_and_free("Error al abrir el infile", p);
	fd_out = open(p->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == ERROR)
		perror_and_free("Error al crear el archivo de salida", p);
	dup2(fd_in, STDIN_FILENO);
	dup2(p->fd[1], STDOUT_FILENO);
	close(p->fd[0]);
	close(fd_in);
	close(fd_out);
	if (execute(p, p->command1) == ERROR)
	{
		write(p->fd[1], &(int){ERROR}, sizeof(int));
		close(p->fd[1]);
	}
}

void	process2(t_pipex *p)
{
	int fd;

	fd = open(p->output, O_WRONLY);
	if (fd == ERROR)
		perror_and_free("Error al abrir el archivo de salida", p);
	dup2(p->fd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(p->fd[0]);
	close(p->fd[1]);
	close(fd);
	execute(p, p->command2);
}