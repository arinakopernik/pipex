# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/17 12:55:54 by lbrianna          #+#    #+#              #
#    Updated: 2022/03/04 16:24:38 by lbrianna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_BONUS = pipex_bonus

SRCS = pipex.c 	utils.c get_path.c\
		ft_split.c\

SRCS_B = pipex_bonus.c utils_bonus.c get_path.c\
		ft_split.c utils.c\

HEADER = pipex.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

OBJS = $(SRCS:%.c=%.o)
OBJS_B = $(SRCS_B:%.c=%.o)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

bonus:	$(NAME_BONUS)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAME_BONUS) : $(OBJS_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME_BONUS)

clean : 
	$(RM) $(OBJS) $(OBJS_B)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PNONY : all, clean, fclean, re, bonus