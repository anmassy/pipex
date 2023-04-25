/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:34:43 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/25 10:56:39 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	get_cmd(t_pipex pipex)
{
	return (1);
}

void	first_child(t_pipex pipex, char **av, char **env)
{
	dup2(pipex.tube[1], STDOUT_FILENO);
	close(pipex.tube[0]);
	pipex.cmd_arg = (ft_split(av[2], ' '));
	pipex.cmd = get_cmd(pipex);
	if (!pipex.cmd)
	{
		error_msg(ERR_CMD);
		exit (1);
	}
	execve(pipex.cmd, pipex.cmd_arg, env);
}

void	second_child(t_pipex pipex, char **av, char **env)
{
	dup2(pipex.tube[0], STDIN_FILENO);
	close(pipex.tube[1]);
	pipex.cmd_arg = (ft_split(av[3], ' '));
	pipex.cmd = get_cmd(pipex);
	if (!pipex.cmd)
	{
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
	return (1);
}
