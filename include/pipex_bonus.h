/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:24:57 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/28 13:30:37 by anmassy          ###   ########.fr       */
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
# define ERR_TUBE "Tube dosen't exist\n"

// typedef int	t_pipe[2];

typedef struct s_pipex
{
	pid_t	pid;
	int		infile;
	int		outfile;
	int		*tube;
	char	*cmd;
	char	*paths;
	char	**cmd_arg;
	char	**cmd_paths;
	int		cmd_num;
	int		dup;
}t_pipex;

/* pipex_bonus.c */
char	*get_path(char **env);

/* child_bonus.c */
char	*get_cmd(char **paths, char *cmd);
void	child(t_pipex pipex, char **av, char **env);

/* error_bonus.c */
int		error_msg(char *err);
int		error_output(char *err);

/* utils_fonction */
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif