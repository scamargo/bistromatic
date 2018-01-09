# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scamargo <scamargo@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/30 21:11:57 by scamargo          #+#    #+#              #
#    Updated: 2018/01/09 11:29:30 by scamargo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
OBJS = $(LIB_SRCS:.c=.o)
NAME = calc
SRCS = main.c

all: $(NAME)

$(NAME):
	$(CC) -Wextra -Wall -Werror $(SRCS) -L. -lft -o $(NAME) -Ilibft/includes

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
