/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:05:44 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/08 22:18:17 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	print(char *s)
{
	write(STDOUT_FILENO, s, ft_strlen(s));
}

void	print_error_cmd(t_pipex *p)
{
	write(STDERR_FILENO, CMD_NOT_FOUND, SIZE_CMD_NOT_FOUND);
	write(STDERR_FILENO, p->args[0], ft_strlen(p->args[0]));
	write(STDERR_FILENO, "\n", 1);
	free_pipex(p);
}

void	print_and_free(char *s, t_pipex *p)
{
	free_pipex(p);
	print(s);
	exit(EXIT_FAILURE);
}

void	perror_and_free(char *s, t_pipex *p)
{
	free_pipex(p);
	perror(s);
	exit(EXIT_FAILURE);
}
