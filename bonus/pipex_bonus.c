/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:24 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/28 13:26:20 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
	int	i;

	i = 0;
	(void)env;
	if (ac < 4)
		error_msg(ERR_INPUT);
	p.infile = open(av[1], O_RDONLY);
	if (p.infile < 0)
		error_output(ERR_INFILE);
	p.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (p.outfile < 0)
		error_output(ERR_OUTFILE);
	// p.tube[2][ac - 3] = malloc (sizeof(t_pipex));
	if (pipe(p.tube[2]) < 0)
		error_msg(ERR_TUBE);
	p.paths = get_path(env);
	p.cmd_paths = ft_split(p.paths, ':');
	child(p, av, env);
	return (0);
}
