/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 22:09:01 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/02 18:20:03 by aquinter         ###   ########.fr       */
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

typedef struct s_pipex
{
	int		fd[2];
	char	**path;
	char	*input;
	char	*command1;
	char	*command2;
	char	*output;
}	t_pipex;

void	ft_bzero(void *s, size_t n);
void	free_matrix(void **mem);
void	print(char *s);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
char	*read_next_line(int fd, char *cache, char *buffer);
char	*build_line(char **cache);
char	*reset_cache(char **cache);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_isascii(int c);
int		clean_cache(char **cache, size_t len, char *nl_ptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
void	print_and_free(char *s, t_pipex *p);
void	perror_and_free(char *s, t_pipex *p);
void	process1(t_pipex *p);
void	process2(t_pipex *p);

#endif
