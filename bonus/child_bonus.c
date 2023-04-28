/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:06:36 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/28 12:47:15 by anmassy          ###   ########.fr       */
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

void	child(t_pipex pipex, char **av, char **env)
{
	int	i;

	i = 0;
	while (i <= pipex.cmd_num)
	{
		printf("%d\n", i);
		pipex.pid = fork();
		if (pipex.pid < 0)
			exit(1);
		if (pipex.pid == 0)
		{
			dup2(pipex.dup, 0);
			if (pipex.cmd + 1 != NULL)
				dup2(pipex.tube[1], 1);
			close(pipex.tube[0]);
			pipex.cmd_arg = ft_split(av[i], ' ');
			pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_arg[0]);
			if (!pipex.cmd || execve (pipex.cmd, pipex.cmd_arg, env) == -1)
			{
				error_msg("erreur\n");
				exit(1);
			}
			exit(1);
		}
		else
		{
			waitpid(pipex.pid, NULL, 0);
			close(pipex.tube[1]);
			pipex.dup = pipex.tube[0];
			i++;
		}
	}
}
