/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 21:31:43 by aquinter          #+#    #+#             */
/*   Updated: 2024/02/26 21:49:01 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int	main(int argc, char *argv[]){

	(void)argc;
	(void)argv;
	int id;
	char *args[]={"/bin/cat", "-e", "/Users/nano/Projects/pipex/readme", NULL};

	id = fork();
	if (id == -1)
		printf("Error executing fork\n");
	if (id == 0){
		int res = execv(args[0], args);
		if (res == -1)
			perror("Error executing command\n");
	}else{
		wait(NULL);
	}
	printf("Hello from main\n");
	return 0;
}