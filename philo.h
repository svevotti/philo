#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

#define ALIVE 0
#define DEAD 1


typedef struct s_info {
	int n_philo;
	unsigned long time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	time_to_think;
}				t_info;

typedef struct s_philo {
	int index;
	struct timeval time;
	pthread_mutex_t *fork_1;
	pthread_mutex_t *fork_2;
	t_info	*info;
}				t_philo;			

//converstion_argv
int ft_atoi(const char *str);

//start program
void create_threads(t_info *info, t_philo **array);














#endif