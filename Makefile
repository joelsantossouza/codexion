# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/31 20:08:50 by joesanto          #+#    #+#              #
#    Updated: 2026/01/31 20:32:54 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= codexion
CC			= cc
FLAGS		= -Wall -Wextra -Werror -g -pthread
SRCS_DIR	= srcs

# ------------------------------ CODER ROUTINE ------------------------------- #
CODER_ROUTINE_DIR		= $(SRCS_DIR)/coder_routine
DONGLE_PROTOCOLS_DIR	= $(CODER_ROUTINE_DIR)/dongle_protocols
SCHEDULERS_DIR			= $(CODER_ROUTINE_DIR)/schedulers

CODER_ROUTINE_HEADERS	+= \
$(addprefix $(CODER_ROUTINE_DIR)/includes, \
	coder.h \
	coder_internal.h \
) \
$(addprefix $(DONGLE_PROTOCOLS_DIR)/includes, \
	dongle_protocols.h \
	dongle_queue.h \
) \
$(addprefix $(SCHEDULERS_DIR)/includes, \
	schedulers.h \
)


CODER_ROUTINE_SRCS		+= \
$(addprefix $(CODER_ROUTINE_DIR)/, \
	coder_routine.c \
	init_coders.c \
	log_coder_event.c \
) \
$(addprefix $(DONGLE_PROTOCOLS_DIR)/, \
	init_dongles.c \
	dongle_queue.c \
	release_two_dongles.c \
	request_two_dongles.c \
) \
$(addprefix $(SCHEDULERS_DIR), \
	wait_fifo_turn.c \
)

HEADERS	+= $(CODER_ROUTINE_HEADERS)
OBJS	+= $(CODER_ROUTINE_SRCS:.c=.o)
# --------------------------------- ERRORS ----------------------------------- #

# ------------------------------- COMPILATION -------------------------------- #
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -O $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
