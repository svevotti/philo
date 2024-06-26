#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR_NUMBER -1

# define EATING 0
# define NOT_EATING 1

# define DONE_EATING 0
# define NOT_DONE_EATING 1

# define DEAD 1
# define STOP_EATING 2

typedef struct s_info {
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				count_max_eat;
	int				terminate_threads;
	pthread_mutex_t	*print;
	pthread_mutex_t	*terminate_lock;
	unsigned long	start_time_ms;
}				t_info;

typedef struct s_philo {
	int				index;
	struct timeval	time;
	long			time_beginning_eating;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*status_lock;
	pthread_mutex_t	*least_status_lock;
	t_info			*info;
	int				status;
	int				least_eating_status;
	int				count_done_eating;
	pthread_t		thread;
}				t_philo;			

//intit program
int		create_threads(t_info *info, t_philo **array);

//utilities
void	free_array(t_philo **array, int size);
int		check_argv(t_info *ptr, int argc);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	do_action(long duration);
void	print_action(t_info *info, int philo, char *str);

//ft_atoi
int		ft_atoi(char *str);

//actions
void	take_a_nap(t_philo *ptr);
int		eat_spaghetti(t_philo *ptr);

//get_time_stamp
int		get_status(t_philo **array, t_info *info);
long	get_time_stamp(void);

//init info
t_philo	**fill_info(t_info *ptr, char **argv, int argc);

#endif
