/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:24 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/27 11:24:43 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	(void)env;
	if (ac < 4)
		error_msg(ERR_INPUT);
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile < 0)
		error_output(ERR_INFILE);
	pipex.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		error_output(ERR_OUTFILE);
	// child(pipex, av, env);
	return (0);
}