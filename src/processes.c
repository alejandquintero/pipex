/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:30:40 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/08 23:22:52 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*build_path_cmd(char *path, char **args)
{
	char	*aux;
	char	*command;

	aux = ft_strjoin(path, "/");
	if (!aux)
		return (NULL);
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
	p->args = ft_split(command, ' ');
	if (!*p->args)
		print_and_free(SYS_ERROR, p);
	if (access(p->args[0], X_OK) == SUCCESS)
		execve(p->args[0], p->args, p->envp);
	while (p->path[i] != NULL)
	{
		p->cmd = build_path_cmd(p->path[i], p->args);
		if (!p->cmd)
			print_and_free(SYS_ERROR, p);
		if (access(p->cmd, X_OK) == SUCCESS)
			execve(p->cmd, p->args, p->envp);
		free(p->cmd);
		i++;
	}
	print_error_cmd(p);
	exit(EXIT_FAILURE);
}

void	process1(t_pipex *p)
{
	dup2(p->input, STDIN_FILENO);
	close(p->pipe[0]);
	dup2(p->pipe[1], STDOUT_FILENO);
	execute(p, p->command1);
}

void	process2(t_pipex *p)
{
	dup2(p->pipe[0], STDIN_FILENO);
	close(p->pipe[1]);
	dup2(p->output, STDOUT_FILENO);
	execute(p, p->command2);
}

int	execute_processes(t_pipex *p)
{
	int	status_pid1;
	int	status_pid2;
	int	pid1;
	int	pid2;

	pid1 = fork();
	if (pid1 == ERROR)
		print_and_free(ERROR_FORK, p);
	if (pid1 == CHILD_PROCESS)
		process1(p);
	wait(&status_pid1);
	pid2 = fork();
	if (pid2 == ERROR)
		print_and_free(ERROR_FORK, p);
	if (pid2 == CHILD_PROCESS)
		process2(p);
	close_pipes(p);
	close_files(p);
	wait(&status_pid2);
	free_pipex(p);
	if (status_pid2 != 0)
		return (PIPEX_ERROR);
	return (PIPEX_SUCCESS);
}
