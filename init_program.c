#include "philo.h"

void	*routine(void *param)
{
	t_philo	*ptr;

	ptr = (t_philo *)param;
	while (1)
	{
		if (eat_spaghetti(ptr) != 0)
			return (NULL);
		take_a_nap(ptr);
		think_life(ptr);
	}
	return (NULL);
}

t_philo	*create_philosopher(int index, pthread_mutex_t *fork, t_info *info)
{
	t_philo			*ptr;

	ptr = (t_philo *)malloc(sizeof(t_philo));
	if (ptr == NULL)
		return (NULL);
	gettimeofday(&(ptr->time), NULL);
	ptr->status = NOT_EATING;
	ptr->least_eating_status = NOT_DONE_EATING;
	ptr->count_done_eating = 0;
	ptr->index = index + 1;
	ptr->right_fork = fork;
	ptr->left_fork = malloc(sizeof(pthread_mutex_t));
	if (ptr->left_fork == NULL)
		return (NULL);
	if (pthread_mutex_init(ptr->left_fork, NULL) != 0)
		return (NULL);
	ptr->info = info;
	return (ptr);
}

int	create_threads(t_info *info, t_philo **array)
{
	pthread_t		thread;
	t_philo			*ptr;
	int				index;
	pthread_mutex_t	*temp_right_fork;

	index = 0;
	temp_right_fork = NULL;
	while (index < info->n_philo)
	{
		ptr = create_philosopher(index, temp_right_fork, info);
		temp_right_fork = ptr->left_fork;
		if (info->n_philo == index + 1 && info->n_philo > 1)
			array[0]->right_fork = temp_right_fork;
		array[index] = ptr;
		index++;
	}
	index = 0;
	while (index < info->n_philo)
	{
		if (pthread_create(&thread, NULL, routine, array[index]) != 0)
			return (1);
		index++;
	}
	return (0);
}
