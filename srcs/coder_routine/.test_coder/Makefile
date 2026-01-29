NAME = test_log_coder_event
CC = cc
FLAGS = -Wall -Wextra -Werror -g

HEADERS = ../includes/coder_internal.h
INCLUDES = -I../includes/
SRCS = test_log_coder_event.c ../log_coder_event.c
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
