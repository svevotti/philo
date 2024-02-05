#include "philo.h"

int	initialize_mutex(t_info *info)
{
	info->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (info->print == NULL)
		return (1);
	pthread_mutex_init(info->print, NULL);
	info->terminate_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (info->terminate_lock == NULL)
		return (1);
	pthread_mutex_init(info->terminate_lock, NULL);
	return (0);
}

t_philo	**fill_info(t_info *ptr, char **argv, int argc)
{
	t_philo	**array;

	ptr->n_philo = ft_atoi(argv[1]);
	ptr->time_to_die = ft_atoi(argv[2]);
	ptr->time_to_eat = ft_atoi(argv[3]);
	ptr->time_to_sleep = ft_atoi(argv[4]);
	ptr->terminate_threads = 0;
	if (argc == 6)
		ptr->count_max_eat = ft_atoi(argv[5]);
	else
		ptr->count_max_eat = -1;
	if (check_argv(ptr, argc) == -1)
	{
		printf("An argument is wrong\n");
		return (NULL);
	}
	array = (t_philo **)malloc(sizeof(t_philo *) * ptr->n_philo);
	if (array == NULL)
		return (NULL);
	if (initialize_mutex(ptr) == 1)
		return (NULL);
	return (array);
}
