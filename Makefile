# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 13:31:34 by anmassy           #+#    #+#              #
#    Updated: 2023/04/27 11:26:16 by anmassy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	srcs/error.c \
		srcs/utils.c \
		srcs/child.c \
		srcs/ft_split.c \
		srcs/free.c \
		srcs/pipex.c

SRC_BONUS =	bonus/pipex_bonus.c \
			bonus/error_bonus.c \
			bonus/utils_bonus.c \
			bonus/child_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
INCS = -I ./include

GREY = \e[0;30m
RED = \e[0;31m
GREEN = \e[0;32m

all : $(NAME)

start:
	@echo "$(GREY)\
 ╔════════════════════════════════════════════════════╗ \n\
 ║                                                    ║ \n\
 ║        ██████╗ ██╗ ██████╗ ███████╗██╗  ██╗        ║ \n\
 ║        ██╔══██╗██║ ██╔══██╗██╔════╝╚██╗██╔╝        ║ \n\
 ║        ██████╔╝██║ ██████╔╝█████╗   ╚███╔╝         ║ \n\
 ║        ██╔═══╝ ██║ ██╔═══╝ ██╔══╝   ██╔██╗         ║ \n\
 ║        ██║     ██║ ██║     ███████╗██╔╝ ██╗        ║ \n\
 ║        ╚═╝     ╚═╝ ╚═╝     ╚══════╝╚═╝  ╚═╝(|)     ║ \n\
 ║                                                    ║ \n\
 ║                    by: anmassy                     ║ \n\
 ║                                                    ║ \n\
 ╚════════════════════════════════════════════════════╝"
	@echo "  ╠═> The code is ready to be executed."
	@echo "  ║"
	@echo "  ╠═> You can run my program with ./pipex and 4 arguments :"
	@echo "  ║        ╚═> ./pipex file1 cmd1 cmd2 file2"
	@echo "  ╚═> Good Luck !"
	@echo "$(GREEN)"

bonus : $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(INCS) $(OBJ_BONUS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJ) start
	@$(CC) $(CFLAGS) $(INCS) $(OBJ) -o $(NAME)

clean :
	@echo "$(RED) Cleaning files..."
	@$(RM) $(OBJ) $(OBJ_BONUS)

fclean : clean
	@echo -n "$(RED)"
	@echo " Cleaning binaries..."
	@$(RM) $(NAME)

re : fclean start
	@echo "$(GREEN) re-make finish"

.PHONY : all bonus clean fclean re
