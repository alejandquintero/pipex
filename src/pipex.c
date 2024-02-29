/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:36:12 by aquinter          #+#    #+#             */
/*   Updated: 2024/02/29 22:52:23 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char *argv[], char *envp[]){

	(void)argc;
	(void)argv;
	char **paths;
	int pid_1;
	int	pid_2;
	int	fds[2];
	int	fd_out;
	char *args_pid1[]={"/bin/cat", "Makefile", NULL};
	char *args_pid2[]={"/usr/bin/grep", "pipe", NULL};

	int i;
	i = 0;	
	paths = NULL;
	while (envp[i] && !paths)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
			{
				printf("Something bad happened");
				return (1);	
			}
		}	
		i++;
	}
	i = 0;
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
	return 0;	
	
	if (pipe(fds) == -1){
		printf("Error in pipe\n");
		return (1);
	}
	pid_1 = fork();
	if (pid_1 == -1){
		printf("Error in pid 1\n");
		return (1);
	}
	if (pid_1 == 0){
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		execv(args_pid1[0], args_pid1);
	}
	pid_2 = fork();
	if (pid_2 == -1){
		printf("Error in pid 2\n");
		return (1);
	}
	if (pid_2 == 0){
		fd_out = open("pipex_results.txt", O_WRONLY);
		if (fd_out == -1){
			printf("Error creating file");
			return 1;
		}
		dup2(fd_out, STDOUT_FILENO);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);		
		close(fds[1]);
		execv(args_pid2[0], args_pid2);
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
	return 0;
}