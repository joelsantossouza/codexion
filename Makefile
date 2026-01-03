# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/03 17:19:47 by joesanto          #+#    #+#              #
#    Updated: 2026/01/03 17:25:08 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread

SRCS_DIR = srcs
OBJS =

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
