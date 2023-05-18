/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:18:58 by anmassy           #+#    #+#             */
/*   Updated: 2023/05/17 13:47:11 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	error_msg(char *err)
{
	int	len;

	len = ft_strlen(err);
	write (1, err, len);
	exit(1);
	return (1);
}

int	error_output(char *err)
{
	perror(err);
	exit (1);
}
