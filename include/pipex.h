/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:24:57 by anmassy           #+#    #+#             */
/*   Updated: 2023/04/21 14:28:50 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* open, unlink */
# include <fcntl.h>

/* to perror */
# include <stdio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* waitpid, wait */
# include <sys/wait.h>

# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_INFILE "Infile not correct" //output_error
# define ERR_OUTFILE "Outfile not correct" //output_error

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int 	
	int	tube[2];
	int	infile;
	int	outfile;
}t_pipex;

/* error.c */
int error_msg(char *err);
int	error_output(char *err);

/* utils.c */
int	ft_strlen(char *s);

#endif

/*
1-Vérifier que les arguments de la ligne de commande sont corrects. //

2-Ouvrir le fichier d'entrée pour le lire. //

3-Créer un tube (pipe) pour rediriger la sortie de la première commande vers l'entrée de la seconde commande.

4-Créer un processus fils pour exécuter la première commande en utilisant l'appel système fork().

5-Dans le processus fils, rediriger la sortie vers l'extrémité d'écriture du tube en utilisant l'appel système dup2().

6-Fermer l'extrémité de lecture du tube dans le processus fils.

7-Exécuter la première commande en utilisant l'appel système execve().

8-Dans le processus parent, créer un second processus fils pour exécuter la deuxième commande en utilisant l'appel système fork().

9-Dans le processus parent, rediriger l'entrée de la deuxième commande vers l'extrémité de lecture du tube en utilisant l'appel système dup2().

10-Fermer l'extrémité d'écriture du tube dans le processus parent.

11-Exécuter la deuxième commande en utilisant l'appel système execve().

12-Attendre la fin de l'exécution des deux processus fils dans le processus parent en utilisant l'appel système waitpid().

13-Écrire le résultat final dans le fichier de sortie.

14-Ce processus permet d'émuler le comportement de la commande Unix pipe en utilisant des tubes, des processus fils et les appels systèmes fork(), dup2(), execve() et waitpid().
*/