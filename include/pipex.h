/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:24:57 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/26 11:36:01 by anmassy          ###   ########.fr       */
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

/* error_message */
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_INFILE "Infile not correct.\n"
# define ERR_OUTFILE "Outfile not correct.\n"
# define ERR_CMD "Command not found.\n"
# define ERR_TUBE "Tube dosen't exist\n"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*cmd;
	char	*paths;
	char	**cmd_arg;
	char	**cmd_paths;
}t_pipex;

/* pipex.c */
char	*get_paths(char **env);

/* error.c */
int		error_msg(char *err);
int		error_output(char *err);

/* utils.c */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);

/* child.c */
void	waiting(t_pipex pipex);
char	*get_cmd(char **paths, char *cmd);
void	first_child(t_pipex pipex, char **av, char **env);
void	second_child(t_pipex pipex, char **av, char **env);
int		child(t_pipex pipex, char **av, char **env);

/* ft_split.c */
int		count_words(char const *str, char c);
char	*word(char const *str, char c);
void	*free_all(char **string, int position);
char	**ft_split(char const *s, char c);

/* free.c */
void	free_child(t_pipex pipex);
void	free_parent(t_pipex pipex);

#endif