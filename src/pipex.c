/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:36:12 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/02 16:58:18 by aquinter         ###   ########.fr       */
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
			{
				print("Error al guardar path\n");
				return (NULL);
			}
		}
		i++;
	}
	if (!path)
		print("No he encontrado PATH, no puedo seguir\n");
	return (path);
}

t_pipex	*init_pipex_struct(char *argv[], char *envp[])
{
	t_pipex	*p;

	p = malloc(sizeof(t_pipex));
	if (!p)
	{
		print("Error al crear la estructura\n");
		return (NULL);
	}
	if (pipe(p->fd) == ERROR)
		print_exit(PIPE_ERROR, p);
	p->input = read_input_command1(argv[1]);
	if (!p->input)
		return (NULL);
	p->path = get_path(envp);
	if (!p->path)
		return (NULL);
	p->command1 = argv[2];
	p->command2 = argv[3];
	p->output = argv[4];
	return (p);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*p;

	atexit(leaks);
	if (argc == MIN_ARGUMENTS)
	{
		p = init_pipex_struct(argv, envp);
		
		if (!p)
			exit_pipex(p);
		print_exit("Todo ok, cierro\n", p);
	}
	else
		print_exit("Parametros incorrectos\n", NULL);
	return (0);
}
