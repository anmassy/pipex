/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 10:48:32 by anmassy           #+#    #+#             */
/*   Updated: 2023/06/21 12:34:05 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*write_line(int fd)
{
	char	*buffer;
	char	line;
	int		ret;
	int		i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	ret = read(fd, &line, 1);
	while (ret > 0)
	{
		buffer[i++] = line;
		if (line == '\n')
			break ;
		ret = read(fd, &line, 1);
	}
	buffer[i] = '\0';
	return (buffer);
}

void	exit_doc(t_pipex p, char *limiter)
{
	char	*line;

	line = "";
	close(p.tube[0]);
	while (line)
	{
		write(1, "pipe heredoc> ", 14);
		line = write_line(0);
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			close(p.tube[1]);
			exit(1);
		}
		write(p.tube[1], line, ft_strlen(line));
		write(p.tube[1], "\n", 1);
		free(line);
	}
	free(line);
	close(p.tube[1]);
	exit(1);
}

void	get_doc(t_pipex p, int ac, char **av)
{
	p.arg = 3;
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
