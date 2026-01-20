# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/03 17:19:47 by joesanto          #+#    #+#              #
#    Updated: 2026/01/20 19:14:48 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread -g

INCLUDES = -Iincludes
HEADERS = includes/codexion.h
SRCS_DIR = srcs

# -------------------------------- UTILS ----------------------------------- #
UTILS_DIR = $(SRCS_DIR)/utils

# ------ TIME MANIPULATION ------- #
TIME_MANIPULATION_DIR = $(UTILS_DIR)/time_manipulation
TIME_MANIPULATION_HEADERS = $(TIME_MANIPULATION_DIR)/time_manipulation.h
TIME_MANIPULATION = $(addprefix $(TIME_MANIPULATION_DIR)/, \
					millis.c \
					timestamp.c \
)
INCLUDES += -I$(TIME_MANIPULATION_DIR)
HEADERS += $(TIME_MANIPULATION_HEADERS)
OBJS += $(TIME_MANIPULATION:.c=.o)

# ----- MUTEX MANIPULATION ------- #
MUTEX_MANIPULATION_DIR = $(UTILS_DIR)/mutex_manipulation
MUTEX_MANIPULATION_HEADERS = $(addprefix $(MUTEX_MANIPULATION_DIR)/, \
			  mutex_set_flag.h \
)
INCLUDES += -I$(MUTEX_MANIPULATION_DIR)
HEADERS += $(MUTEX_MANIPULATION_HEADERS)

# ----- QUEUE MANIPULATION ------ #
QUEUE_MANIPULATION_DIR = $(UTILS_DIR)/queue_manipulation
QUEUE_MANIPULATION_HEADERS = $(QUEUE_MANIPULATION_DIR)/queue.h
INCLUDES += -I$(QUEUE_MANIPULATION_DIR)
HEADERS += $(QUEUE_MANIPULATION_HEADERS)

# ----------------------------- ERRORS ------------------------------------- #
ERRORS_DIR = $(SRCS_DIR)/errors
ERRORS_HEADERS = $(ERRORS_DIR)/includes/errors.h
ERRORS = $(addprefix $(ERRORS_DIR)/, get_error_str.c)
INCLUDES += -I$(ERRORS_DIR)/includes
HEADERS += $(ERRORS_HEADERS)
OBJS += $(ERRORS:.c=.o)

# ----------------------------- PARSING ------------------------------------ #
PARSING_DIR = $(SRCS_DIR)/parsing
PARSING_HEADERS = $(addprefix $(PARSING_DIR)/includes/, \
				  private_codexion_parser.h \
				  public_codexion_parser.h \
)
PARSING = $(addprefix $(PARSING_DIR)/, codexion_parser.c codexion_parser_utils.c)
INCLUDES += -I$(PARSING_DIR)/includes
HEADERS += $(PARSING_HEADERS)
OBJS += $(PARSING:.c=.o)

# --------------------------- CODER ROUTINE -------------------------------- #
CODER_ROUTINE_DIR = $(SRCS_DIR)/coder_routine
CODER_ROUTINE_HEADERS = $(addprefix $(CODER_ROUTINE_DIR)/includes/, \
						private_coder_routine.h \
						public_coder_routine.h \
)
CODER_ROUTINE = $(addprefix $(CODER_ROUTINE_DIR)/, \
				coder_routine.c \
				coder_routine_utils.c \
)
INCLUDES += -I$(CODER_ROUTINE_DIR)/includes
HEADERS += $(CODER_ROUTINE_HEADERS)
OBJS += $(CODER_ROUTINE:.c=.o)

# --------------------------- MONITOR ROUTINE ------------------------------ #
MONITOR_ROUTINE_DIR = $(SRCS_DIR)/monitor_routine
MONITOR_ROUTINE_HEADERS = $(addprefix $(MONITOR_ROUTINE_DIR)/includes/, \
						  private_monitor_routine.h \
						  public_monitor_routine.h \
)
MONITOR_ROUTINE = $(addprefix $(MONITOR_ROUTINE_DIR)/, \
				  schedule_fifo.c \
				  monitor_routine.c \
				  monitor_routine_utils.c \
)
INCLUDES += -I$(MONITOR_ROUTINE_DIR)/includes
HEADERS += $(MONITOR_ROUTINE_HEADERS)
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
