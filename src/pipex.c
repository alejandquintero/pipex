/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:36:12 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/02 18:51:52 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	leaks(void)
{
	system("leaks -q pipex");
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
	p->input = argv[1];
	p->command1 = argv[2];
	p->command2 = argv[3];
	p->output = argv[4];
	return (p);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*p;
	int	pid1;
	int	pid2;

	atexit(leaks);
	if (argc == MIN_ARGUMENTS)
	{
		p = init_pipex_struct(argv, envp);
		pid1 = fork();
		if (pid1 == ERROR)
			print_and_free("Error al duplicar proceso 1\n", p);
		if (pid1 == CHILD_PROCESS)
			process1(p);
		waitpid(pid1, NULL, 0);
		pid2 = fork();
		if (pid2 == ERROR)
			print_and_free("Error al duplicar proceso 2\n", p);
		if (pid2 == CHILD_PROCESS)
			process2(p);
		close(p->fd[0]);
		close(p->fd[1]);
		waitpid(pid2, NULL, 0);
		// print_and_free("Todo ok, cierro\n", p);
	}
	else
		print("Parametros incorrectos\n");
	return (0);
}
