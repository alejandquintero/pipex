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
	dup2(p->input, STDIN_FILENO);
	close(p->fd[0]);
	dup2(p->fd[1], STDOUT_FILENO);
	if (execute(p, p->command1) == ERROR)
		exit(EXIT_FAILURE);
}

void	process2(t_pipex *p)
{
	dup2(p->fd[0], STDIN_FILENO);
	close(p->fd[1]);
	dup2(p->output, STDOUT_FILENO);
	execute(p, p->command2);
}