CC = gcc 

SRCS = $(wildcard *.c)

NAME = philo

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g -pthread -fsanitize=thread

%.o:%.c *.h
	$(CC) $(CFLAGS) -c $< -o $@

all: *.h
	@$(MAKE) $(NAME)

$(NAME): $(OBJS)
	
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all