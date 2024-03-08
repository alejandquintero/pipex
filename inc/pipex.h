/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 22:09:01 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/08 22:16:51 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include "constants.h"
# include <stdint.h>

typedef struct s_pipex
{
	int		pipe[2];
	char	**path;
	int		output;
	int		input;
	char	*command1;
	char	*command2;
	char	**envp;
	char	*cmd;
	char	**args;
}	t_pipex;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);
int		execute_processes(t_pipex *p);
int		ft_isascii(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	free_matrix(void **mem);
void	print(char *s);
void	print_and_free(char *s, t_pipex *p);
void	perror_and_free(char *s, t_pipex *p);
void	process1(t_pipex *p);
void	process2(t_pipex *p);
void	free_pipex(t_pipex *p);
void	open_files(t_pipex *p, char *argv[]);
void	close_files(t_pipex *p);
void	close_pipes(t_pipex *p);
void	print_error_cmd(t_pipex *p);

#endif
