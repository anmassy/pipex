/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:06:36 by anmassy           #+#    #+#             */
/*   Updated: 2023/06/30 15:28:07 by anmassy          ###   ########.fr       */
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
	int		i;

	i = 0;
	while (p.cmd_paths[i])
	{
		cmd_slash = ft_strjoin(p.cmd_paths[i], "/");
		p.cmd = ft_strjoin(cmd_slash, *p.cmd_arg);
		free(cmd_slash);
		if (access(p.cmd, F_OK) == 0)
		{
			if (execve (p.cmd, p.cmd_arg, env) == -1)
			{
				free(p.cmd);
				free_child(&p);
				free_parent(&p);
				error_msg(ERR_CMD);
			}
		}
		free(p.cmd);
		i++;
	}
	return (NULL);
}

void	ft_duplicate(t_pipex p)
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
}

void	child(t_pipex p, char **av, char **env)
{
	p.pid = fork();
	if (p.pid < 0)
		error_output(ERR_TUBE);
	if (p.pid == 0)
	{
		ft_duplicate(p);
		close_pipes(&p);
		p.cmd_arg = ft_split(av[2 + p.here_doc + p.arg], ' ');
		if (!get_exec(p, env))
		{
			free_child(&p);
			free_parent(&p);
			error_msg(ERR_CMD);
		}
	}
}
