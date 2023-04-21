/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:25:40 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/21 13:05:31 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex pipex;

	if (ac != 5)
		error_msg(ERR_INPUT);
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile < 0)
		error_output(ERR_INFILE);
	pipex.outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.outfile < 0)
		error_output(ERR_OUTFILE);
	child(pipex, av, env);
	return (0);
}