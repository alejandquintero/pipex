/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:30:40 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/05 22:39:10 by aquinter         ###   ########.fr       */
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

void	execute(t_pipex *p, char *command)
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
		{
			if (execve(p->cmd, p->cmd_args, p->envp) == -1)
				perror("error al ejecutarse el comando");	
		}
		free(p->cmd);
		i++;
	}
	write(STDERR_FILENO, "pipex: command not found: ", 26);
	write(STDERR_FILENO, p->cmd_args[0], ft_strlen(p->cmd_args[0]));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	process1(t_pipex *p)
{
	int		fd;	

	fd = open(p->input, O_RDONLY);
	if (fd == ERROR)
		perror_and_free("Error al abrir el infile", p);
	dup2(fd, STDIN_FILENO);
	dup2(p->fd[1], STDOUT_FILENO);
	close(p->fd[0]);
	close(p->fd[1]);
	close(fd);
	execute(p, p->command1);
}

void	process2(t_pipex *p)
{
	int fd;

	fd = open(p->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == ERROR)
		perror_and_free("Error al crear el archivo de salida", p);
	dup2(p->fd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(p->fd[0]);
	close(p->fd[1]);
	close(fd);
	execute(p, p->command2);
}