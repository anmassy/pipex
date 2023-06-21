/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:24 by anmassy           #+#    #+#             */
/*   Updated: 2023/06/21 14:39:07 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	*ft_memset(void *s, int c, int n)
{
	int				i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

void	creat_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_nbr - 1)
	{
		if (pipe(p->tube + 2 * i) < 0)
			error_msg(ERR_PIPE);
		i++;
	}
}

void	close_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->pipe_nmbs)
	{
		close(p->tube[i]);
		i++;
	}
}

void	open_files(t_pipex *p, int ac, char **av)
{
	p->infile = open(av[1], O_RDONLY);
	if (p->infile < 0)
		error_output(ERR_INFILE);
	p->outfile = open(av[ac - 1], O_APPEND | O_CREAT | O_RDWR, 0644);
	if (p->outfile < 0)
		error_output(ERR_OUTFILE);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;

	if (ac < 5)
		error_msg(ERR_INPUT);
	ft_memset(&p, 0, sizeof(t_pipex));
	if (ft_strncmp("here_doc", av[1], 8) == 0)
		get_doc(p, ac, av);
	else
		open_files(&p, ac, av);
	p.cmd_nbr = ac - 3;
	p.tube_nbr = 2 * (p.cmd_nbr - 1);
	p.tube = (int *)malloc(sizeof(int) * p.tube_nbr);
	// if (!p.tube)
		// free
	p.paths = get_path(env);
	p.cmd_paths = ft_split(p.paths, ':');
	creat_pipes(&p);
	p.arg = -1;
	while (++(p.arg) < p.cmd_nbr)
		child(p, av, env);
	close_pipes(&p);
	waitpid(-1, NULL, 0);
	//freeparent
	return (0);
}
