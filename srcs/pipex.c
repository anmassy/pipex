/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:25:40 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/25 10:56:53 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	waiting(t_pipex pipex)
{
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
}

void	close_tubes(t_pipex pipex)
{
	close(pipex.tube[0]);
	close(pipex.tube[1]);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac != 5)
		error_msg(ERR_INPUT);
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile < 0)
		error_output(ERR_INFILE);
	pipex.outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.outfile < 0)
		error_output(ERR_OUTFILE);
	if (!child(pipex, av, env))
		return (0);
	waiting(pipex);
	close_tubes(pipex);
	return (0);
}
