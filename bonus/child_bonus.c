/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:06:36 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/28 13:30:22 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*slash;
	char	*command;

	while (*paths)
	{
		slash = ft_strjoin(*paths, "/");
		command = ft_strjoin(slash, cmd);
		free(slash);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	child(t_pipex p, char **av, char **env)
{
	int	i;

	i = 0;
	while (i <= p.cmd_num)
	{
		p.pid = fork();
		if (p.pid < 0)
			exit(1);
		if (p.pid == 0)
		{
			dup2(p.dup, 0);
			dup2(p.tube[1], 1);
			close(p.tube[0]);
			p.cmd_arg = ft_split(av[i + 2], ' ');
			p.cmd = get_cmd(p.cmd_paths, p.cmd_arg[0]);
			if (!p.cmd || execve (p.cmd, p.cmd_arg, env) == -1)
			{
				error_msg("erreur\n");
				exit(1);
			}
			exit(1);
		}
		else
		{
			waitpid(p.pid, NULL, 0);
			close(p.tube[1]);
			p.dup = p.tube[0];
			i++;
		}
	}
}
