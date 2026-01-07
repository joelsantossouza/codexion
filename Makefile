# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/03 17:19:47 by joesanto          #+#    #+#              #
#    Updated: 2026/01/07 13:45:35 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread

INCLUDES = -Iincludes
HEADERS = includes/codexion.h
SRCS_DIR = srcs

# ----------------------------- ERRORS ------------------------------------- #
ERRORS_DIR = $(SRCS_DIR)/errors
ERRORS_HEADERS = $(ERRORS_DIR)/includes/parsing_errors.h
ERRORS = $(addprefix $(ERRORS_DIR)/, get_error_str.c)
INCLUDES += -I$(ERRORS_DIR)/includes
OBJS += $(ERRORS:.c=.o)

# ----------------------------- PARSING ------------------------------------ #
PARSING_DIR = $(SRCS_DIR)/parsing
PARSING_HEADERS = $(PARSING_DIR)/includes/codexion_parser.h
PARSING = $(addprefix $(PARSING_DIR)/, codexion_parser.c parsing_utils.c)
INCLUDES += -I$(PARSING_DIR)/includes
HEADERS += $(PARSING_HEADERS)
OBJS += $(PARSING:.c=.o)

# ----------------------------- GET RULES ---------------------------------- #
GET_RULES_DIR = $(SRCS_DIR)/get_rules
GET_RULES = $(addprefix $(GET_RULES_DIR)/, get_coder_rules.c \
			get_monitor_rules.c \
)
OBJS += $(GET_RULES:.c=.o)

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
