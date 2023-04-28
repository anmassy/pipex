/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:34:43 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/28 17:51:29 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_waiting(t_pipex p)
{
	waitpid(p.pid1, NULL, 0);
	waitpid(p.pid2, NULL, 0);
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

void	first_child(t_pipex p, char **av, char **env)
{
	dup2(p.tube[1], 1);
	close(p.tube[0]);
	close(p.tube[1]);
	dup2(p.infile, 0);
	close(p.infile);
	close(p.outfile);
	p.cmd_arg = ft_split(av[2], ' ');
	p.cmd = get_cmd(p.cmd_paths, p.cmd_arg[0]);
	if (!p.cmd || execve(p.cmd, p.cmd_arg, env) == -1)
	{
		free_child(p);
		error_msg(ERR_CMD);
		exit (1);
	}
}

void	second_child(t_pipex p, char **av, char **env)
{
	dup2(p.tube[0], 0);
	close(p.tube[0]);
	close(p.tube[1]);
	dup2(p.outfile, 1);
	close(p.infile);
	close(p.outfile);
	p.cmd_arg = ft_split(av[3], ' ');
	p.cmd = get_cmd(p.cmd_paths, p.cmd_arg[0]);
	if (!p.cmd || execve(p.cmd, p.cmd_arg, env) == -1)
	{
		free_child(p);
		error_msg(ERR_CMD);
		exit (1);
	}
}

int	child(t_pipex p, char **av, char **env)
{
	p.pid1 = fork();
	if (p.pid1 < 0)
		return (0);
	if (p.pid1 == 0)
		first_child(p, av, env);
	p.pid2 = fork();
	if (p.pid2 < 0)
		return (0);
	if (p.pid2 == 0)
		second_child(p, av, env);
	close(p.tube[0]);
	close(p.tube[1]);
	ft_waiting(p);
	return (1);
}
