NAME = philo
CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS =	main.c start.c utils.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -fsanitize=address

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I .

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
