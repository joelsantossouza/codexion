NAME = test_dongle_protocols
CC = cc
FLAGS = -Wall -Wextra -Werror -g

HEADERS = ../../../monitor_routine/simulation_control/includes/simulation_control.h \
		  ../../../errors/includes/errors.h ../../includes/coder.h \
		  ../../../utils/time_utils/time_utils.h \
		  ../includes/dongle_protocols.h

INCLUDES = -I../../../monitor_routine/simulation_control/includes/ \
		   -I../../../errors/includes/ -I../../includes \
		   -I../../../utils/time_utils/ -I../includes \

SRCS = test_dongle_protocols.c ../release_two_dongles.c \
	   ../request_two_dongles.c ../../log_coder_event.c \
	   ../dongle_queue.c ../../schedulers/wait_fifo_turn.c \
	   ../../../monitor_routine/simulation_control/monitored_wait_until.c \
	   ../../../monitor_routine/simulation_control/simulation_control.c \
	   ../../../utils/time_utils/time_utils.c

OBJS = $(SRCS:.c=.o)

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
