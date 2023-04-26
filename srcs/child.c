/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:34:43 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/26 11:30:33 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	waiting(t_pipex pipex)
{
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*slash;
	char	*command;

	while (*paths)
	{
		slash = ft_strjoin(*paths, "/");
		command = ft_strjoin(slash, cmd);
		free(slash);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char **av, char **env)
{
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	dup2(pipex.infile, 0);
	pipex.cmd_arg = ft_split(av[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_arg[0]);
	if (!pipex.cmd)
	{
		free_child(pipex);
		error_msg(ERR_CMD);
		exit (1);
	}
	execve(pipex.cmd, pipex.cmd_arg, env);
}

void	second_child(t_pipex pipex, char **av, char **env)
{
	dup2(pipex.tube[0], 0);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_arg = ft_split(av[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_arg[0]);
	if (!pipex.cmd)
	{
		free_child(pipex);
		error_msg(ERR_CMD);
		exit (1);
	}
	execve(pipex.cmd, pipex.cmd_arg, env);
}

int	child(t_pipex pipex, char **av, char **env)
{
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		return (0);
	if (pipex.pid1 == 0)
		first_child(pipex, av, env);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		return (0);
	if (pipex.pid2 == 0)
		second_child(pipex, av, env);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	return (1);
}
