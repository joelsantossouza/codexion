# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/03 17:19:47 by joesanto          #+#    #+#              #
#    Updated: 2026/01/15 11:19:02 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread -g

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
GET_RULES = $(addprefix $(GET_RULES_DIR)/, \
			get_coder_rules.c \
			get_monitor_rules.c \
)
OBJS += $(GET_RULES:.c=.o)

# --------------------------TIME MANIPULATION ------------------------------ #
TIME_MANIPULATION_DIR = $(SRCS_DIR)/time_manipulation
TIME_MANIPULATION = $(addprefix $(TIME_MANIPULATION_DIR)/, \
					millis.c \
					spend_time.c \
					time_elapsed.c \
)
OBJS += $(TIME_MANIPULATION:.c=.o)

# ---------------------------- MUTEX UTILS --------------------------------- #
MUTEX_UTILS_DIR = $(SRCS_DIR)/mutex_utils
MUTEX_UTILS = $(addprefix $(MUTEX_UTILS_DIR)/, \
			  mutex_log_msg.h \
			  mutex_set_flag.h \
)
INCLUDES += -I$(MUTEX_UTILS_DIR)
HEADERS += $(MUTEX_UTILS)

# --------------------------- CODER ROUTINE -------------------------------- #
CODER_ROUTINE_DIR = $(SRCS_DIR)/coder_routine
CODER_ROUTINE_HEADERS = $(CODER_ROUTINE_DIR)/includes/coder_routine.h
CODER_ROUTINE = $(addprefix $(CODER_ROUTINE_DIR)/, \
				coder_routine.c \
				coder_routine_utils.c \
)
INCLUDES += -I$(CODER_ROUTINE_DIR)/includes
HEADERS += $(CODER_ROUTINE_HEADERS)
OBJS += $(CODER_ROUTINE:.c=.o)

# --------------------------- MONITOR ROUTINE ------------------------------ #
MONITOR_ROUTINE_DIR = $(SRCS_DIR)/monitor_routine
MONITOR_ROUTINE = $(addprefix $(MONITOR_ROUTINE_DIR)/, \
				  fifo_scheduler.c \
				  start_monitoring.c \
)
OBJS += $(MONITOR_ROUTINE:.c=.o)

# -------------------------------- MAIN ------------------------------------ #
MAIN = $(SRCS_DIR)/main.c
OBJS += $(MAIN:.c=.o)

# ----------------------------- COMPILATION -------------------------------- #

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
