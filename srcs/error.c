/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:18:58 by anmassy           #+#    #+#             */
/*   Updated: 2023/06/30 15:27:56 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "string.h"

void	error_msg(char *err)
{
	int	len;

	len = ft_strlen(err);
	write (2, err, len);
	exit(1);
}

void	error_output(char *err)
{
	perror(err);
	exit(1);
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
}

void	close_and_leave(t_pipex *p)
{
	close(p->infile);
	close(p->outfile);
	error_msg(ERR_ENV);
	exit(1);
}
