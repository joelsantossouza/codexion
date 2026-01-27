NAME = test_parsing
CC = cc
FLAGS = -Wall -Wextra -Werror -g

HEADERS = ../includes/public_codexion_parser.h ../../errors/includes/errors.h
INCLUDES = -I../includes -I../../errors/includes
SRCS = test_parsing.c ../codexion_parser.c ../codexion_parser_utils.c \
	   ../../errors/get_error_str.c
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
