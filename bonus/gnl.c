/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 10:48:32 by anmassy           #+#    #+#             */
/*   Updated: 2023/05/14 11:12:33 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

# define BUFFER_SIZE 2048

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((char)c == s[i])
			return (s + i);
		i++;
	}
	if (c == 0)
		return ((char *)(s + i));
	return (0);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*strings;
	size_t	size;
	size_t	j;

	size = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (len < (size_t)ft_strlen(s))
		strings = (char *)malloc(sizeof(*s) * (len + 1));
	else
		strings = (char *)malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (!strings)
		return (NULL);
	while (size != start && s[size])
		size++;
	while (s[size] && j < len)
		strings[j++] = s[size++];
	if (size >= start - 1)
		free(s);
	if (j == 0)
		return (free(strings), NULL);
	strings[j] = '\0';
	return (strings);
}

int	size_line(char *strings, int i)
{
	if (!strings)
		return (-1);
	while (1)
	{
		if (strings[i] == '\n' || strings[i] == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char		*strings;
	char			*buffer;
	char			*line;
	int				ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	ret = read(fd, buffer, BUFFER_SIZE);
	while (ret > 0)
	{
		buffer[ret] = '\0';
		strings = ft_strjoin(strings, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		ret = read(fd, buffer, BUFFER_SIZE);
	}
	line = ft_substr(strings, 0, (size_line(strings, 0) + 1));
	ret = size_line(strings, 0) + 1;
	strings = ft_substr(strings, ret, (ft_strlen(strings) - ret));
	return (free(buffer), line);
}



// size_t	ft_strlen1(const char *s)
// {
// 	size_t	x;

// 	x = 0;
// 	while (s[x])
// 		x++;
// 	return (x);
// }

// char	*ft_strcpy(char *dst, const char *src)
// {
// 	int	x;

// 	x = 0;
// 	while (src[x])
// 	{
// 		dst[x] = src[x];
// 		x++;
// 	}
// 	dst[x] = '\0';
// 	return (dst);
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	char	*ptr;
// 	size_t	x;

// 	x = 0;
// 	ptr = (void *)malloc(count * size);
// 	if (!ptr)
// 		return (NULL);
// 	while (x < count * size)
// 	{
// 		ptr[x] = 0;
// 		x++;
// 	}
// 	return ((void *)ptr);
// }

// char	*ft_strdup(const char *s1)
// {
// 	char	*str;
// 	size_t	l;
// 	size_t	x;

// 	x = 0;
// 	l = ft_strlen1(s1);
// 	str = (void *)malloc(sizeof(*str) * (l + 1));
// 	if (!str)
// 		return (NULL);
// 	while (x < l)
// 	{
// 		*(str + x) = *(s1 + x);
// 		x++;
// 	}
// 	str[x] = '\0';
// 	return (str);
// }

// static char	*ft_new_line_checker(char *s)
// {
// 	int	x;

// 	x = 0;
// 	if (!s)
// 		return (0);
// 	while (s[x])
// 	{
// 		if (s[x] == '\n')
// 			return ((char *)s + x);
// 		x++;
// 	}
// 	return (NULL);
// }

// static int	ft_checker_mallocer(int fd, char **line, char **buf)
// {
// 	if ((read(fd, NULL, 0) < 0) || !line || (BUFFER_SIZE <= 0))
// 		return (-1);
// 	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!*buf)
// 		return (-1);
// 	return (0);
// }

// static void	ft_connector_liberator(char **line, char *buf)
// {
// 	char	*mem_liber;

// 	mem_liber = *line;
// 	*line = ft_strjoin(*line, buf);
// 	free(mem_liber);
// }

// static char	*ft_sump_checker(char **sump, char **line)
// {
// 	char	*p_nline;

// 	p_nline = NULL;
// 	if (*sump)
// 	{
// 		p_nline = ft_new_line_checker(*sump);
// 		if (p_nline)
// 		{
// 			*p_nline = '\0';
// 			*line = ft_strdup(*sump);
// 			ft_strcpy(*sump, ++p_nline);
// 		}
// 		else
// 		{
// 			*line = ft_strdup(*sump);
// 			free(*sump);
// 			*sump = NULL;
// 		}
// 	}
// 	else
// 		*line = ft_calloc(sizeof(char), 1);
// 	return (p_nline);
// }

// int	get_next_line(int fd, char **line)
// {
// 	static char	*sump;
// 	char		*buf;
// 	char		*p_nline;
// 	int			qbr;

// 	p_nline = NULL;
// 	qbr = 1;
// 	if (ft_checker_mallocer(fd, line, &buf) < 0)
// 		return (-1);
// 	p_nline = ft_sump_checker(&sump, line);
// 	while (!p_nline && qbr > 0)
// 	{
// 		qbr = read(fd, buf, BUFFER_SIZE);
// 		buf[qbr] = '\0';
// 		p_nline = ft_new_line_checker(buf);
// 		if (p_nline)
// 		{
// 			*p_nline = '\0';
// 			sump = ft_strdup(++p_nline);
// 		}
// 		ft_connector_liberator(line, buf);
// 	}
// 	free(buf);
// 	return (qbr && sump);
// }