/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:52:55 by anmassy           #+#    #+#             */
/*   Updated: 2023/06/30 12:30:26 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	count_words(char const *str, char c)
{
	int	total;
	int	i;

	i = 0;
	total = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			total++;
		while (str[i] != c && str[i])
		i++;
	}
	return (total);
}

char	*word(char const *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	word = (char *)malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] != c && str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

void	*free_all(char **string, int position)
{
	int	i;

	i = 0;

	while (i < position)
	{
		free(string[i]);
		i++;
	}
	free(string);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**string;

	if (!s)
		return (NULL);
	len = count_words(s, c);
	i = -1;
	string = (char **)malloc((len + 1) * sizeof(char *));
	if (!string)
		return (NULL);
	while (++i < len)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			string[i] = word(s, c);
		if (!(string[i]))
			return (free_all(string, i));
		while (*s && *s != c)
			s++;
	}
	string[i] = 0;
	return (string);
}
