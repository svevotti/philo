#include "philo.h"

void	think(t_philo *philo)
{
	long	duration;

	duration = (philo->info->time_to_die - philo->info->time_to_eat
			- philo->info->time_to_sleep) / 2;
	print_action(philo->info, philo->index, "is thinking");
	do_action(duration);
}

void	*routine(void *param)
{
	t_philo	*ptr;
	int		terminate_status;

	ptr = (t_philo *)param;
	if (ptr->index % 2 == 0)
		do_action((ptr->info->time_to_die - ptr->info->time_to_eat
				- ptr->info->time_to_sleep) / 2);
	while (1)
	{
		if (eat_spaghetti(ptr) != 0)
			return (NULL);
		take_a_nap(ptr);
		think(ptr);
		pthread_mutex_lock(ptr->info->terminate_lock);
		terminate_status = ptr->info->terminate_threads;
		pthread_mutex_unlock(ptr->info->terminate_lock);
		if (terminate_status == 1)
			return (NULL);
	}
	return (NULL);
}

t_philo	*create_philosopher(int index, pthread_mutex_t *fork, t_info *info)
{
	t_philo			*ptr;

	ptr = (t_philo *)malloc(sizeof(t_philo));
	if (ptr == NULL)
		return (NULL);
	ptr->time_beginning_eating = get_time_stamp();
	ptr->status = NOT_EATING;
	ptr->least_eating_status = NOT_DONE_EATING;
	ptr->count_done_eating = 0;
	ptr->index = index + 1;
	ptr->left_fork = fork;
	ptr->right_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (ptr->right_fork == NULL)
		return (NULL);
	if (pthread_mutex_init(ptr->right_fork, NULL) != 0)
		return (NULL);
	ptr->status_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ptr->status_lock, NULL);
	ptr->least_status_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ptr->least_status_lock, NULL);
	ptr->info = info;
	return (ptr);
}

int	create_threads(t_info *info, t_philo **array)
{
	t_philo			*ptr;
	int				index;
	pthread_mutex_t	*temp_left_fork;

	index = 0;
	temp_left_fork = NULL;
	info->start_time_ms = get_time_stamp();
	while (index < info->n_philo)
	{
		ptr = create_philosopher(index, temp_left_fork, info);
		if (ptr == NULL)
			return (1);
		temp_left_fork = ptr->right_fork;
		if (info->n_philo == index + 1 && info->n_philo > 1)
			array[0]->left_fork = temp_left_fork;
		array[index++] = ptr;
	}
	index = 0;
	while (index < info->n_philo)
	{
		ptr = array[index++];
		if (pthread_create(&(ptr->thread), NULL, routine, ptr) != 0)
			return (1);
	}
	return (0);
}
