CC = cc
#FLAGS = -Werror -Wextra -Wall
NAME = philo
PHILO_FILES = main.c convertion_argv.c start_program.c
PHILO_OBJ = $(PHILO_FILES:.c=.o)

all: $(NAME)

$(NAME): $(PHILO_OBJ)
#		$(CC) $(FLAGS) $(PHILO_OBJ) -o $(NAME)
		$(CC) $(PHILO_OBJ) -o $(NAME)

%.o: %.c
	$(CC) -c $^

clean:
		rm -f $(PHILO_OBJ)
fclean: clean
		rm -f $(NAME)
re: fclean all
.PHONY: clean fclean re all
