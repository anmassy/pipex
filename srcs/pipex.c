/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:25:40 by anmassy           #+#    #+#             */
/*   Updated: 2023/06/21 15:02:54 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	p;

	if (ac != 5)
		error_msg(ERR_INPUT);
	p.infile = open(av[1], O_RDONLY);
	if (p.infile < 0)
		error_msg(ERR_INFILE);
	p.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (p.outfile < 0)
		error_output(ERR_OUTFILE);
	if (pipe(p.tube) < 0)
		error_output(ERR_TUBE);
	p.paths = get_path(env);
	p.cmd_paths = ft_split(p.paths, ':');
	child(&p, av, env);
	close(p.infile);
	close(p.outfile);
	waitpid(p.pid1, NULL, 0);
	waitpid(p.pid2, NULL, 0);
	free_parent(&p);
	return (0);
}
