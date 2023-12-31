#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define ALIVE 0
# define DEAD 1

# define EATING 0
# define NOT_EATING 1

# define DONE_EATING 0
# define NOT_DONE_EATING 1

typedef struct s_info {
	int				n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_think;
	unsigned int	count_max_eat;
}				t_info;

typedef struct s_philo {
	int				index;
	struct timeval	time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
	int				status;
	int				least_eating_status;
	int				count_done_eating;
}				t_philo;			

//converstion_argv
int		ft_atoi(const char *str);

//start program
int		create_threads(t_info *info, t_philo **array);

//utilis functions main
void	free_array(t_philo **array, int size);

//utilis functions start program
void	think_life(t_philo *ptr);
void	take_a_nap(t_philo *ptr);
void	eat_spaghetti(t_philo *ptr);

#endif