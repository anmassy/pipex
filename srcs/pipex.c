/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:25:40 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/28 15:46:34 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path(char **env)
{
	while (*env && ft_strncmp("PATH", *env, 4))
		env++;
	if (!*env)
		return (ft_strjoin("", ""));
	return (ft_strjoin(*env + 5, ""));
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;

	if (ac != 5)
		error_msg(ERR_INPUT);
	p.infile = open(av[1], O_RDONLY);
	if (p.infile < 0)
		error_output(ERR_INFILE);
	p.outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (p.outfile < 0)
		error_output(ERR_OUTFILE);
	if (pipe(p.tube) < 0)
		error_msg(ERR_TUBE);
	p.paths = get_path(env);
	p.cmd_paths = ft_split(p.paths, ':');
	child(p, av, env);
	close(p.infile);
	close(p.outfile);
	free_parent(p);
	return (0);
}
