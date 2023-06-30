/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:06:36 by anmassy           #+#    #+#             */
/*   Updated: 2023/06/30 12:54:37 by anmassy          ###   ########.fr       */
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

char	*get_exec(t_pipex p, char **env)
{
	char	*cmd_slash;

	while (*p.cmd_paths)
	{
		cmd_slash = ft_strjoin(*p.cmd_paths, "/");
		p.cmd = ft_strjoin(cmd_slash, *p.cmd_arg);
		free(cmd_slash);
		if (access(p.cmd, F_OK) == 0)
		{
			if (execve (p.cmd, p.cmd_arg, env) == -1)
			{
				free_child(&p);
				error_msg(ERR_CMD);
			}
		}
		free(p.cmd);
		p.cmd_paths++;
	}
	return (NULL);
}

void	child(t_pipex p, char **av, char **env)
{
	p.pid = fork();
	if (p.pid < 0)
		error_output(ERR_TUBE);
	if (p.pid == 0)
	{
		if (p.arg == 0)
		{
			dup2(p.infile, 0);
			dup2(p.tube[1], 1);
		}
		else if (p.arg == p.cmd_nbr - 1)
		{
			dup2(p.tube[2 * p.arg - 2], 0);
			dup2(p.outfile, 1);
		}
		else
		{
			dup2(p.tube[2 * p.arg - 2], 0);
			dup2(p.tube[2 * p.arg + 1], 1);
		}
		close_pipes(&p);
		p.cmd_arg = ft_split(av[2 + p.arg], ' ');
		if (!get_exec(p, env))
		{
			free_child(&p);
			free_parent(&p);
			error_msg(ERR_CMD);
		}
	}
}
