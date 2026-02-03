# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/31 20:08:50 by joesanto          #+#    #+#              #
#    Updated: 2026/02/03 16:01:21 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= codexion
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -pthread
LDFLAGS		=
SRCS_DIR	= srcs
MAX_CODERS	= 200

# ------------------------------ CODER ROUTINE ------------------------------- #
CODER_ROUTINE_DIR		= $(SRCS_DIR)/coder_routine
DONGLE_PROTOCOLS_DIR	= $(CODER_ROUTINE_DIR)/dongle_protocols
SCHEDULERS_DIR			= $(CODER_ROUTINE_DIR)/schedulers

CODER_ROUTINE_HEADERS	= \
$(addprefix $(CODER_ROUTINE_DIR)/includes/, \
	coder.h \
	coder_internal.h \
) \
$(addprefix $(DONGLE_PROTOCOLS_DIR)/includes/, \
	dongle_protocols.h \
	dongle_queue.h \
) \
$(addprefix $(SCHEDULERS_DIR)/includes/, \
	schedulers.h \
)


CODER_ROUTINE_INCLUDES	= \
	-I$(CODER_ROUTINE_DIR)/includes \
	-I$(DONGLE_PROTOCOLS_DIR)/includes \
	-I$(SCHEDULERS_DIR)/includes


CODER_ROUTINE_SRCS		= \
$(addprefix $(CODER_ROUTINE_DIR)/, \
	coder_routine.c \
	coder_utils.c \
	log_coder_event.c \
) \
$(addprefix $(DONGLE_PROTOCOLS_DIR)/, \
	dongle_utils.c \
	dongle_queue.c \
	release_two_dongles.c \
	request_two_dongles.c \
) \
$(addprefix $(SCHEDULERS_DIR)/, \
	wait_fifo_turn.c \
	wait_edf_turn.c \
)

HEADERS		+= $(CODER_ROUTINE_HEADERS)
INCLUDES	+= $(CODER_ROUTINE_INCLUDES)
OBJS		+= $(CODER_ROUTINE_SRCS:.c=.o)

# --------------------------------- ERRORS ----------------------------------- #
ERRORS_DIR		= $(SRCS_DIR)/errors

ERRORS_HEADERS	= $(ERRORS_DIR)/includes/errors.h

ERRORS_INCLUDES	= -I$(ERRORS_DIR)/includes

ERRORS_SRCS		= $(ERRORS_DIR)/get_error_msg.c

HEADERS		+= $(ERRORS_HEADERS)
INCLUDES	+= $(ERRORS_INCLUDES)
OBJS		+= $(ERRORS_SRCS:.c=.o)

# ----------------------------- MONITOR ROUTINE ------------------------------ #
MONITOR_ROUTINE_DIR			= $(SRCS_DIR)/monitor_routine
SIMULATION_CONTROL_DIR		= $(MONITOR_ROUTINE_DIR)/simulation_control

MONITOR_ROUTINE_HEADERS		= \
	$(MONITOR_ROUTINE_DIR)/includes/monitor.h \
	$(SIMULATION_CONTROL_DIR)/includes/simulation_control.h

MONITOR_ROUTINE_INCLUDES	= \
	-I$(MONITOR_ROUTINE_DIR)/includes \
	-I$(SIMULATION_CONTROL_DIR)/includes

MONITOR_ROUTINE_SRCS		= \
$(addprefix $(SIMULATION_CONTROL_DIR)/, \
	monitored_wait_until.c \
	simulation_control.c \
) \
	$(MONITOR_ROUTINE_DIR)/monitor_routine.c

HEADERS		+= $(MONITOR_ROUTINE_HEADERS)
INCLUDES	+= $(MONITOR_ROUTINE_INCLUDES)
OBJS		+= $(MONITOR_ROUTINE_SRCS:.c=.o)

# --------------------------------- PARSING ---------------------------------- #
PARSING_DIR			= $(SRCS_DIR)/parsing

PARSING_HEADERS		= \
$(addprefix $(PARSING_DIR)/includes/, \
	codexion_parser.h \
	codexion_parser_internal.h \
)

PARSING_INCLUDES	= -I$(PARSING_DIR)/includes

PARSING_SRCS		= \
$(addprefix $(PARSING_DIR)/, \
	codexion_parser.c \
	codexion_parser_utils.c \
)

HEADERS		+= $(PARSING_HEADERS)
INCLUDES	+= $(PARSING_INCLUDES)
OBJS		+= $(PARSING_SRCS:.c=.o)

# ---------------------------------- UTILS ----------------------------------- #
UTILS_DIR					= $(SRCS_DIR)/utils
CODEXION_CONFIG_UTILS_DIR	= $(UTILS_DIR)/codexion_config_utils
TIME_UTILS_DIR				= $(UTILS_DIR)/time_utils

UTILS_HEADERS	= \
	$(CODEXION_CONFIG_UTILS_DIR)/codexion_config_control.h \
	$(TIME_UTILS_DIR)/time_utils.h

UTILS_INCLUDES	= \
	-I$(CODEXION_CONFIG_UTILS_DIR) \
	-I$(TIME_UTILS_DIR)

UTILS_SRCS		= \
	$(CODEXION_CONFIG_UTILS_DIR)/codexion_config_control.c \
	$(TIME_UTILS_DIR)/time_utils.c

HEADERS		+= $(UTILS_HEADERS)
INCLUDES	+= $(UTILS_INCLUDES)
OBJS		+= $(UTILS_SRCS:.c=.o)

# ---------------------------------- MAIN ------------------------------------ #
MAIN_DIR		= $(SRCS_DIR)

MAIN_HEADERS	= includes/codexion.h

MAIN_INCLUDES	= -Iincludes

MAIN_SRCS		= $(MAIN_DIR)/main.c

HEADERS		+= $(MAIN_HEADERS)
INCLUDES	+= $(MAIN_INCLUDES)
OBJS		+= $(MAIN_SRCS:.c=.o)

# ------------------------------- COMPILATION -------------------------------- #
all: $(NAME)

fsanitize: CFLAGS+=-fsanitize=thread
fsanitize: LDFLAGS+=-fsanitize=thread
fsanitize: fclean $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -DMAX_CODERS=$(MAX_CODERS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
