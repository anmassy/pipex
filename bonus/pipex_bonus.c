/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:24 by anmassy           #+#    #+#             */
/*   Updated: 2023/05/14 11:13:37 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		(*(unsigned char *)(s + i) = (unsigned char)c);
		i++;
	}
	return (s);
}

void	exit_doc(t_pipex p, char *limiter)
{
	char	*line;

	close(p.tube[0]);
	write(1, "pipe heredoc> ", 14);
	line = "";
	while (line)
	{
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0)
		{
			free(line);
			close(p.tube[1]);
			exit(1);
		}
		write(p.tube[1], line, ft_strlen(line));
		write(p.tube[1], "\n", 1);
		write(1, "pipe heredoc> ", 14);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(p.tube[1]);
	exit(1);
}

void	get_doc(t_pipex p, int ac, char **av, int arg)
{
	arg = 3;
	if (ac < 6)
		error_msg(ERR_INPUT);
	if (pipe(p.tube) < 0)
		error_msg(ERR_TUBE);
	p.pid = fork();
	if (p.pid == 0)
		exit_doc(p, av[2]);
	else
	{
		close(p.tube[1]);
		if (dup2(p.tube[0], 0) == -1)
			error_msg(ERR_DUP);
		close(p.tube[0]);
		waitpid(p.pid, NULL, 0);
	}
	p.outfile = open(av[ac - 1], O_APPEND | O_CREAT | O_RDWR, 0644);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;
	int		arg;

	arg = 0;
	if (ac < 4)
		error_msg(ERR_INPUT);
	ft_memset(&p, 0, sizeof(t_pipex));
	if (ft_strncmp("here_doc", av[1], 8) == 0)
		get_doc(p, ac, av, arg);
	else
	{
		arg = 2;
		p.infile = open(av[1], O_RDONLY);
		if (p.infile < 0)
			error_output(ERR_INFILE);
		p.outfile = open(av[ac - 1], O_APPEND | O_CREAT | O_RDWR, 0644);
		if (p.outfile < 0)
			error_output(ERR_OUTFILE);
		if (dup2(p.infile, 0) == -1)
			error_msg(ERR_DUP);
	}
	p.paths = get_path(env);
	p.cmd_paths = ft_split(p.paths, ':');
	while (arg < ac - 2)
		child(p, av[arg++], env);
	if (dup2(p.outfile, 1) == -1)
		error_msg(ERR_DUP);
	get_exec(p, av[ac - 2], env);
	return (0);
}
