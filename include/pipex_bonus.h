/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:24:57 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/27 11:26:48 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* open, unlink */
# include <fcntl.h>

/* to perror */
# include <stdio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* waitpid, wait */
# include <sys/wait.h>

/* error_message */
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_INFILE "Infile not correct.\n"
# define ERR_OUTFILE "Outfile not correct.\n"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
}t_pipex;

/* error_bonus.c */
int	error_msg(char *err);
int	error_output(char *err);

/* utils_bonus.c */
int	ft_strlen(char *s);

#endif