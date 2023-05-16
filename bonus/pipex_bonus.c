/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:24 by anmassy           #+#    #+#             */
/*   Updated: 2023/05/16 11:51:04 by anmassy          ###   ########.fr       */
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

void	open_file(t_pipex p, int ac, char **av)
{
	p.infile = open(av[1], O_RDONLY);
	if (p.infile < 0)
		error_output(ERR_INFILE);
	p.outfile = open(av[ac - 1], O_APPEND | O_CREAT | O_RDWR, 0644);
	if (p.outfile < 0)
		error_output(ERR_OUTFILE);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;
	int		arg;

	arg = 2;
	if (ac < 4)
		error_msg(ERR_INPUT);
	ft_memset(&p, 0, sizeof(t_pipex));
	if (ft_strncmp("here_doc", av[1], 8) == 0)
		get_doc(p, ac, av, arg);
	else
	{
		open_file(p, ac, av);
		if (dup2(p.infile, 0) == -1)
			error_msg(ERR_DUP);
		close(p.infile);
	}
	p.paths = get_path(env);
	p.cmd_paths = ft_split(p.paths, ':');
	while (arg < ac - 2)
		child(p, av[arg++], env);
	if (dup2(p.outfile, 1) == -1)
		error_msg(ERR_DUP);
	close(p.outfile);
	get_exec(p, av[ac - 2], env);
	return (0);
}
