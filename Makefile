# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/03 17:19:47 by joesanto          #+#    #+#              #
#    Updated: 2026/01/06 16:40:50 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread

INCLUDES = -Iincludes
HEADERS = includes/codexion.h
SRCS_DIR = srcs

# ----------------------------- PARSING ------------------------------------ #
PARSING_DIR = $(SRCS_DIR)/parsing
PARSING_HEADERS = $(addprefix $(PARSING_DIR)/includes/, codexion_parser.h \
				  parsing_errors.h \
)
PARSING = $(addprefix $(PARSING_DIR)/, codexion_parser.c parsing_errors.c \
		  parsing_utils.c \
)
INCLUDES += -I$(PARSING_DIR)/includes
HEADERS += $(PARSING_HEADERS)
OBJS += $(PARSING:.c=.o)

# -------------------------------- MAIN ------------------------------------ #
MAIN = $(SRCS_DIR)/main.c
OBJS += $(MAIN:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
