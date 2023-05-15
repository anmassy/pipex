/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 10:48:32 by anmassy           #+#    #+#             */
/*   Updated: 2023/05/15 11:19:37 by anmassy          ###   ########.fr       */
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
	ret = read(fd, &line, BUFFER_SIZE - BUFFER_SIZE + 1);
	while (ret > 0)
	{
		buffer[i++] = line;
		if (line == '\n')
			break ;
		ret = read(fd, &line, BUFFER_SIZE - BUFFER_SIZE + 1);
	}
	buffer[i] = '\0';
	return (buffer);
}
