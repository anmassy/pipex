/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:24:57 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/25 10:57:36 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_INFILE "Infile not correct"
# define ERR_OUTFILE "Outfile not correct"
# define ERR_CMD "Command not found"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	**cmd_arg;
	char	*cmd;
	int		path;
}t_pipex;

/* pipex.c */
void	waiting(t_pipex pipex);
void	close_tubes(t_pipex pipex);

/* error.c */
int		error_msg(char *err);
int		error_output(char *err);

/* utils.c */
int		ft_strlen(char *s);

/* child.c */
void	first_child(t_pipex pipex, char **av, char **env);
void	second_child(t_pipex pipex, char **av, char **env);
int		child(t_pipex pipex, char **av, char **env);

/* ft_split.c */
int		count_words(char const *str, char c);
char	*word(char const *str, char c);
void	*free_all(char **string, int position);
char	**ft_split(char const *s, char c);

/* free.c */

#endif