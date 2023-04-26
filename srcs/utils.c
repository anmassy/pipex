/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:24:04 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/26 11:29:46 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && (n > 0))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new;
	size_t	len_suf;
	size_t	len_pre;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len_pre = ft_strlen(s1);
	len_suf = ft_strlen(s2);
	new = (char *)malloc ((len_pre + len_suf + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = 0;
	return (new);
}
