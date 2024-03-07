/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:36:12 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/06 20:19:12 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	leaks(void)
{
	system("leaks -q pipex");
}

void	open_files(t_pipex *p, char *argv[])
{
	p->input = open(argv[1], O_RDONLY);
	if (p->input == ERROR)
		perror_and_free("Error al abrir el infile", p);
	p->output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->output == ERROR)
		perror_and_free("Error al crear el archivo de salida", p);
}

char	**get_path(char *envp[])
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (envp[i] && !path)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			if (!path)
				return (NULL);
		}
		i++;
	}
	if (!path)
		return (NULL);
	return (path);
}

t_pipex	*init_pipex_struct(char *argv[], char *envp[])
{
	t_pipex	*p;

	p = ft_calloc(1, sizeof(t_pipex));
	if (!p)
		print_and_free("Error al crear la estructura\n", NULL);
	if (pipe(p->fd) == ERROR)
		print_and_free(PIPE_ERROR, p);
	p->path = get_path(envp);
	if (!p->path)
		print_and_free("Error al localizar PATH\n", p);
	p->command1 = argv[2];
	p->command2 = argv[3];
	p->envp = envp;
	p->cmd = NULL;
	p->cmd_args = NULL;
	open_files(p, argv);
	return (p);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*p;
	int	status_pid1;
	int	pid1;
	int	pid2;

	// atexit(leaks);
	if (argc == MIN_ARGUMENTS)
	{
		p = init_pipex_struct(argv, envp);
		pid1 = fork();
		if (pid1 == ERROR)
			print_and_free("Error al duplicar proceso 1\n", p);
		if (pid1 == CHILD_PROCESS)
			process1(p);
		else
		{
			waitpid(pid1, &status_pid1, 0);
			if (status_pid1 == 0)
			{
				pid2 = fork();
				if (pid2 == ERROR)
					print_and_free("Error al duplicar proceso 2\n", p);
				if (pid2 == CHILD_PROCESS)
					process2(p);
				close(p->fd[0]);
				close(p->fd[1]);
				close(p->input);
				close(p->output);
			}
			waitpid(pid2, NULL, 0);
			free_pipex(p);
		}
	}
	else
		print("Parametros incorrectos\n");
	return (0);
}
