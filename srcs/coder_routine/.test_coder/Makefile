NAME = test_log_coder_event
CC = cc
FLAGS = -Wall -Wextra -Werror -g

HEADERS = ../includes/coder_internal.h ../../errors/includes/errors.h \
		  ../../monitor_routine/simulation_control/includes/simulation_control.h
INCLUDES = -I../includes/ -I../../utils/time_utils/ -I../../errors/includes \
		   -I../../monitor_routine/simulation_control/includes
SRCS = test_log_coder_event.c ../log_coder_event.c ../../utils/time_utils/time_utils.c \
	   ../../monitor_routine/simulation_control/simulation_control.c
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
