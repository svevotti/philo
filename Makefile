CC = cc
FLAGS = -Wextra -Wall -pthread -g -Werror #-fsanitize=thread 
NAME = philo
PHILO_FILES = init_program.c utilities.c actions.c ft_atoi.c main.c \
				get_time_stamp.c init_info.c
PHILO_OBJ = $(PHILO_FILES:.c=.o)

all: $(NAME)

$(NAME): $(PHILO_OBJ)
		$(CC) $(FLAGS) $(PHILO_OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $^

clean:
		rm -f $(PHILO_OBJ) main.o
fclean: clean
		rm -f $(NAME)
re: fclean all
.PHONY: clean fclean re all
