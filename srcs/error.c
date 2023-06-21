/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:18:58 by anmassy           #+#    #+#             */
/*   Updated: 2023/06/21 14:35:06 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "string.h"

void	error_msg(char *err)
{
	int	len;

	len = ft_strlen(err);
	write (2, err, len);
	exit(1);
}

void	error_output(char *err)
{
	perror(err);
	exit(1);
}
