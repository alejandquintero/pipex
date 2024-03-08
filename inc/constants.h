/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:26:44 by aquinter          #+#    #+#             */
/*   Updated: 2024/03/08 22:10:05 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define SIZE_CMD_NOT_FOUND 19
# define CHILD_PROCESS 0
# define MIN_ARGUMENTS 5
# define PIPEX_SUCCESS 0
# define PIPEX_ERROR 1
# define SUCCESS 0
# define ERROR -1
# define PIPE_ERROR "Something was wrong executing pipe\n"
# define SYS_ERROR "Something was wrong in the system\n"
# define CMD_NOT_FOUND "Command not found: "
# define ERROR_FORK "Error executing fork\n"
# define INVALID_ARGV "Expected exactly four arguments\n"
# define ERROR_PATH "Cannot find key PATH\n"
# define PATH_CMDS "PATH="
# define ERROR_INFILE "Error infile: "
# define ERROR_OUTFILE "Error infile: "

#endif
