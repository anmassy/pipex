/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:25:40 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/26 16:55:37 by anmassy          ###   ########.fr       */
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
	t_pipex	pipex;

	if (ac != 5)
		error_msg(ERR_INPUT);
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile < 0)
		error_output(ERR_INFILE);
	pipex.outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		error_output(ERR_OUTFILE);
	if (pipe(pipex.tube) < 0)
		error_msg(ERR_TUBE);
	pipex.paths = get_path(env);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	if (child(pipex, av, env) == 0)
		return (0);
	close(pipex.infile);
	close(pipex.outfile);
	free_parent(pipex);
	return (0);
}
