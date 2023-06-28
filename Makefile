# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 13:31:34 by anmassy           #+#    #+#              #
#    Updated: 2023/06/28 15:18:14 by anmassy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	srcs/ft_split.c \
		srcs/ft_strlen.c \
		srcs/ft_strncmp.c \
		srcs/ft_strjoin.c \
		srcs/error.c \
		srcs/child.c \
		srcs/pipex.c

SRC_BONUS =	bonus/ft_split.c \
			bonus/ft_strlen.c \
			bonus/ft_strncmp.c \
			bonus/ft_strjoin.c \
			bonus/pipex_bonus.c \
			bonus/error_bonus.c \
			bonus/child_bonus.c \
			bonus/write_line.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f
INCS = -I ./include

GREY = \e[0;30m
RED = \e[0;31m
GREEN = \e[0;32m

all : $(NAME)

$(NAME): $(OBJ)
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
	@$(CC) $(CFLAGS) $(INCS) $(OBJ) -o $(NAME)
	@echo "  ╠═> compile with : $(CFLAGS)"
	@echo "  ║"
	@echo "  ╠═> The code is ready to be executed."
	@echo "  ║"
	@echo "  ╠═> You can run my program with ./pipex and 4 arguments :"
	@echo "  ║        ╚═> ./pipex file1 cmd1 cmd2 file2"
	@echo "  ╚═> Don't destroy my code !"
	@echo ""
	
bonus : $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(INCS) $(OBJ_BONUS) -o $(NAME)
	@echo "   ╚═> compile with : $(CFLAGS)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@


clean :
	@echo "$(RED) Cleaning files..."
	@$(RM) $(OBJ) $(OBJ_BONUS)

fclean : clean
	@echo -n "$(RED)"
	@echo " Cleaning binaries..."
	@$(RM) $(NAME)

re : fclean all
	@echo "$(GREEN) re-make finish"

.PHONY : all bonus clean fclean re
