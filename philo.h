#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>


typedef struct s_philo {

	int	philo;
	int *finished;
	// int	n_forks;
	// int	time_to_die;
	// int	time_to_eat;
	// int	time_to_sleep;
	// int	time_to_think;
	// int i;
	// int single_philosopher;
	// int	action;
	pthread_mutex_t lock;
	// int	index;
}	t_philo;

//converstion_argv
int ft_atoi(const char *str);

//start program
void create_threads(int count, int *finished);














#endif