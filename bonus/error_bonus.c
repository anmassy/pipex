/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:18:58 by anmassy           #+#    #+#             */
/*   Updated: 2023/06/21 15:08:55 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	error_msg(char *err)
{
	int	len;

	len = ft_strlen(err);
	write (1, err, len);
	exit(1);
	return (1);
}

int	error_output(char *err)
{
	perror(err);
	exit (1);
}

void	free_parent(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->cmd_paths[i])
	{
		free(p->cmd_paths[i]);
		i++;
	}
	free(p->cmd_paths);
	free(p->paths);
	free(p->tube);
}

void	free_child(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->cmd_arg[i])
	{
		free(p->cmd_arg[i]);
		i++;
	}
	free(p->cmd_arg);
	free(p->cmd);
}