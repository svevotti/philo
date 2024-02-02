#include "philo.h"

int		check_status(t_philo *element, int *count_done_eating);
int		is_alive(t_philo *ptr, long time_die);

long	get_time_stamp(void)
{
	struct timeval	time_stamp;
	long	time_stamp_ms;

	gettimeofday(&time_stamp, NULL);
	time_stamp_ms = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	return (time_stamp_ms);
}

int	get_status(t_philo **array, t_info *info)
{
	int				i;
	int				count_done_eating;

	i = 0;
	count_done_eating = 0;
	while (i < info->n_philo)
	{
		if (check_status(array[i], &count_done_eating) == 1)
			return (DEAD);
		i++;
	}
	if (count_done_eating == info->n_philo)
	{
		pthread_mutex_lock(info->terminate_lock);
		info->terminate_threads = 1;
		pthread_mutex_unlock(info->terminate_lock);
		return (STOP_EATING);
	}
	return (0);
}

int	check_status(t_philo *element, int *count_done_eating)
{
	int	eating_status;
	int	least_eating_status;

	pthread_mutex_lock(element->least_status_lock);
	least_eating_status = element->least_eating_status;
	pthread_mutex_unlock(element->least_status_lock);
	if (least_eating_status == DONE_EATING)
		*count_done_eating = *count_done_eating + 1;
	pthread_mutex_lock(element->status_lock);
	eating_status = element->status;
	pthread_mutex_unlock(element->status_lock);
	if (eating_status && is_alive(element, element->info->time_to_die) == DEAD)
	{
		print_action(element->info, element->index, "has died");
		return (1);
	}
	return (0);
}

int	is_alive(t_philo *ptr, long time_die)
{
	long	total_difference;
	long	current_time;

	current_time = get_time_stamp();
	pthread_mutex_lock(ptr->status_lock);
	total_difference = current_time - ptr->time_beginning_eating;
	pthread_mutex_unlock(ptr->status_lock);
	if (total_difference >= time_die)
	{
		pthread_mutex_lock(ptr->info->terminate_lock);
		ptr->info->terminate_threads = 1;
		pthread_mutex_unlock(ptr->info->terminate_lock);
		return (1);
	}
	return (0);
}
