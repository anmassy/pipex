/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 08:56:31 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/28 13:16:13 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_child(t_pipex p)
{
	int	i;

	i = 0;
	while (p.cmd_arg[i])
	{
		free(p.cmd_arg[i]);
		i++;
	}
	free(p.cmd_arg);
	free(p.cmd);
}

void	free_parent(t_pipex p)
{
	int	i;

	i = 0;
	while (p.cmd_paths[i])
	{
		free(p.cmd_paths[i]);
		i++;
	}
	free(p.cmd_paths);
	free(p.paths);
}
