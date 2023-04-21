/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:34:43 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/21 14:27:51 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// get_cmd

void	child_one(t_pipex pipex, char **av, char **env) //etape 4 5 6
{
	dup2(pipex.tube[1], 1); //int dup2(int oldfd, int newfd);
	close(pipex.tube[0]);
	execve(av[0], av[2], env); //int execve(const char *fichier, char *const argv[],char *const envp[]);  
}

void	child_two(t_pipex pipex, char **av, char **env) //etape 8 9 10 11 
{
	dup2(pipex.tube[0], 1); //int dup2(int oldfd, int newfd);
	close(pipex.tube[1]);
	execve(av[0], av[3], env); //int execve(const char *fichier, char *const argv[],char *const envp[]);  
}

void	child(t_pipex pipex, char **av, char **env)
{
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child_one(pipex, av, env); //infile
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child_two(pipex, av, env); //outfile
}