NAME = test_parsing
CC = cc
FLAGS = -Wall -Wextra -Werror -g
MAX_CODERS = 200

HEADERS = ../includes/codexion_parser.h ../../errors/includes/errors.h \
		  ../../monitor_routine/simulation_control/includes/simulation_control.h \
		  ../../utils/codexion_config_utils/codexion_config_control.h
INCLUDES = -I../includes -I../../errors/includes/ \
		   -I../../monitor_routine/simulation_control/includes/ \
		  -I../../utils/codexion_config_utils/ -I../../coder_routine/includes/ \
		  -I../../coder_routine/dongle_protocols/includes/ -I../../../includes/ \
		  -I../../coder_routine/schedulers/includes/ -I../../utils/time_utils/
SRCS = test_parsing.c ../codexion_parser.c ../codexion_parser_utils.c \
	   ../../errors/get_error_msg.c ../../coder_routine/schedulers/wait_fifo_turn.c \
	   ../../monitor_routine/simulation_control/monitored_wait_until.c \
	   ../../monitor_routine/simulation_control/simulation_control.c \
	   ../../coder_routine/dongle_protocols/dongle_queue.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(INCLUDES) -DMAX_CODERS=$(MAX_CODERS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
