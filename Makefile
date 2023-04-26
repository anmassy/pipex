# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 13:31:34 by anmassy           #+#    #+#              #
#    Updated: 2023/04/26 10:14:09 by anmassy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	srcs/error.c \
		srcs/utils.c \
		srcs/child.c \
		srcs/ft_split.c \
		srcs/free.c \
		srcs/pipex.c

OBJ = $(SRC:.c=.o)

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
INCS = -I ./include

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCS) $(OBJ) -o $(NAME)

clean :
	@$(RM) $(OBJ) >/dev/null

fclean : clean
	@$(RM) $(NAME) >/dev/null

re : fclean all

.PHONY : all clean fclean re
