/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:24 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/26 15:14:09 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	child(t_pipex pipex, char **av, char **env)
{
	int	i;

	i = 0;
	dup2(pipex.tube[0], 1);
	close(pipex.tube[fd]);
	close(pipex.tube[fd]);
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

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 4)
		error_msg(ERR_INPUT);
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile < 0)
		error_output(ERR_INFILE);
	pipex.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		error_output(ERR_OUTFILE);
	child(pipex, av, env);
	
		
}