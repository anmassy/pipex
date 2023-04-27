/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:06:36 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/27 10:20:12 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

// void	child(t_pipex pipex, char **av, char **env)
// {
// 	int	i;

// 	i = 0;
// 	dup2(pipex.tube[0], 1);
// 	close(pipex.tube[fd]);
// 	close(pipex.tube[fd]);
// 	dup2(pipex.infile, 0);
// 	pipex.cmd_arg = ft_split(av[2], ' ');
// 	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_arg[0]);
// 	if (!pipex.cmd)
// 	{
// 		free_child(pipex);
// 		error_msg(ERR_CMD);
// 		exit (1);
// 	}
// 	execve(pipex.cmd, pipex.cmd_arg, env);
// }
