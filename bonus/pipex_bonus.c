/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:24 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/29 12:58:04 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

// int	get_doc(t_pipex p, int ac, char **av, int arg)
// {
// 	if (ft_strncmp("here_doc", av[1], 8))
// 	{
// 		arg = 3;
		
// 		p.outfile = open(av[ac - 1], O_TRUNC | O_APPEND | O_CREAT | O_RDWR, 0644);
// 	}
// }

int	main(int ac, char **av, char **env)
{
	t_pipex	p;
	int		arg;

	if (ac < 4)
		error_msg(ERR_INPUT);
	arg = 2;
	p.infile = open(av[1], O_RDONLY);
	if (p.infile < 0)
		error_output(ERR_INFILE);
	p.outfile = open(av[ac - 1], O_TRUNC | O_APPEND | O_CREAT | O_RDWR, 0644);
	if (p.outfile < 0)
		error_output(ERR_OUTFILE);
	p.paths = get_path(env);
	p.cmd_paths = ft_split(p.paths, ':');
	if (dup2(p.infile, 0) == -1)
		error_msg(ERR_DUP);
	while (arg < ac - 2)
		child(p, av[arg++], env);
	if (dup2(p.outfile, 1) == -1)
		error_msg(ERR_DUP);
	get_exec(p, av[ac - 2], env);
	return (0);
}
