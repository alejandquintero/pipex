/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:36:12 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/09 11:19:21 by aquinter         ###   ########.fr       */
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
		if (ft_strncmp(envp[i], PATH_CMDS, 5) == 0)
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
		print_and_free(SYS_ERROR, NULL);
	if (pipe(p->pipe) == ERROR)
		print_and_free(PIPE_ERROR, p);
	p->path = get_path(envp);
	if (!p->path)
		print_and_free(ERROR_PATH, p);
	p->command1 = argv[2];
	p->command2 = argv[3];
	p->envp = envp;
	p->cmd = NULL;
	p->args = NULL;
	open_files(p, argv);
	return (p);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*p;

	// atexit(leaks);
	if (argc == MIN_ARGUMENTS)
	{
		p = init_pipex_struct(argv, envp);
		return (execute_processes(p));
	}
	print(INVALID_ARGV);
	return (PIPEX_ERROR);
}
