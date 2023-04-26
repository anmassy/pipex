/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 08:56:31 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/26 11:36:09 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_child(t_pipex pipex)
{
	int	i;

	i = 0;
	while (pipex.cmd_arg[i])
	{
		free(pipex.cmd_arg[i]);
		i++;
	}
	free(pipex.cmd_arg);
	free(pipex.cmd);
}

void	free_parent(t_pipex pipex)
{
	int	i;

	i = 0;
	while (pipex.cmd_paths[i])
	{
		free(pipex.cmd_paths[i]);
		i++;
	}
	free(pipex.cmd_paths);
	free(pipex.paths);
}
