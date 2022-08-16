CC = gcc 

SRCS = action_utils.c actions.c check_args.c death.c init_simul.c \
       main.c utils.c

NAME = philo

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g -pthread

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
