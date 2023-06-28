/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 10:48:32 by anmassy           #+#    #+#             */
/*   Updated: 2023/06/28 15:24:01 by anmassy          ###   ########.fr       */
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

void	exit_doc(t_pipex *p, char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error_msg(ERR_INFILE);
	line = "";
	while (line)
	{
		write(1, "pipe heredoc> ", 14);
		line = write_line(0);
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
	p->infile = open(".heredoc_tmp", O_RDONLY);
	if (p->infile < 0)
		error_msg(ERR_INFILE);
}
