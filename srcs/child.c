/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:34:43 by anmassy           #+#    #+#             */
/*   Updated: 2023/06/30 12:33:03 by anmassy          ###   ########.fr       */
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

char	*get_exec(t_pipex *p, char **env)
{
	char	*cmd_slash;

	if (p->paths == NULL)
		error_msg(ERR_PATHS);
	while (*p->cmd_paths)
	{
		cmd_slash = ft_strjoin(*p->cmd_paths, "/");
		p->cmd = ft_strjoin(cmd_slash, p->cmd_arg[0]);
		free(cmd_slash);
		if (access(p->cmd, F_OK) == 0)
			if (execve (p->cmd, p->cmd_arg, env) == -1)
			{
				free_child(p);
				error_msg(ERR_CMD);
			}
		free(p->cmd);
		p->cmd_paths++;
	}
	return (NULL);
}

void	first_child(t_pipex *p, char **av, char **env)
{
	if (dup2(p->tube[1], 1) == -1)
		error_output(ERR_DUP);
	close(p->tube[0]);
	close(p->tube[1]);
	if (dup2(p->infile, 0) == -1)
		error_output(ERR_DUP);
	close(p->infile);
	close(p->outfile);
	p->cmd_arg = ft_split(av[2], ' ');
	if (!get_exec(p, env))
	{
		free_child(p);
		error_msg(ERR_CMD);
	}
}

void	second_child(t_pipex *p, char **av, char **env)
{
	if (dup2(p->tube[0], 0) == -1)
		error_output(ERR_DUP);
	close(p->tube[1]);
	close(p->tube[0]);
	if (dup2(p->outfile, 1) == -1)
		error_output(ERR_DUP);
	close(p->infile);
	close(p->outfile);
	p->cmd_arg = ft_split(av[3], ' ');
	if (!get_exec(p, env))
	{
		free_child(p);
		error_msg(ERR_CMD);
	}
}

void	child(t_pipex *p, char **av, char **env)
{
	p->pid1 = fork();
	if (p->pid1 < 0)
		error_output(ERR_TUBE);
	if (p->pid1 == 0)
		first_child(p, av, env);
	p->pid2 = fork();
	if (p->pid2 < 0)
		error_output(ERR_TUBE);
	if (p->pid2 == 0)
		second_child(p, av, env);
	close(p->tube[0]);
	close(p->tube[1]);
}
