/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:34:43 by anmassy           #+#    #+#             */
/*   Updated: 2023/05/23 14:08:21 by anmassy          ###   ########.fr       */
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

char	*get_exec(t_pipex p, char *av, char **env)
{
	char	*cmd_slash;

	p.cmd_arg = ft_split(av, ' ');
	if (p.paths == NULL)
		error_msg(ERR_PATHS);
	while (*p.cmd_paths)
	{
		cmd_slash = ft_strjoin(*p.cmd_paths, "/");
		p.cmd = ft_strjoin(cmd_slash, *p.cmd_arg);
		free(cmd_slash);
		if (access(p.cmd, F_OK) == 0)
		{
			if (execve (p.cmd, p.cmd_arg, env) == -1)
				error_output(ERR_CMD);
		}
		free(p.cmd);
		p.cmd_paths++;
	}
	return (NULL);
}

void	child(t_pipex p, char *av, char **env)
{
	if (pipe(p.tube) < 0)
		error_output(ERR_TUBE);
	p.pid = fork();
	if (p.pid < 0)
		error_output(ERR_TUBE);
	if (p.pid == 0)
	{
		close(p.tube[0]);
		if (dup2(p.tube[1], 1) == -1)
			error_output(ERR_DUP);
		close(p.tube[1]);
		close(p.outfile);
		get_exec(p, av, env);
	}
	else
	{
		close(p.tube[1]);
		if (dup2(p.tube[0], 0) == -1)
			error_output(ERR_DUP);
		close(p.tube[0]);
		waitpid(p.pid, NULL, 0);
	}
}
