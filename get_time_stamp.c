#include "philo.h"

int		check_status(t_philo *element, struct timeval time_stamp,
			int i, int *count_done_eating);
int		is_alive(t_philo *ptr, struct timeval current_time,
			unsigned long time_die);

int	get_status(t_philo **array, t_info *info)
{
	int				i;
	int				count_done_eating;
	struct timeval	time;

	i = 0;
	count_done_eating = 0;
	gettimeofday(&time, NULL);
	while (i < info->n_philo)
	{
		if (check_status(array[i], time, i, &count_done_eating) == 1)
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

int	check_status(t_philo *element, struct timeval time_stamp,
					int i, int *count_done_eating)
{
	unsigned long	time_in_ms;
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
	if (eating_status && is_alive(element, time_stamp, element->info->time_to_die) == DEAD)
	{
		time_in_ms = (time_stamp.tv_sec * 1000 + time_stamp.tv_usec / 1000) - element->info->start_time_ms;
		pthread_mutex_lock(element->info->print);
		printf("\033[1;31m%lu philosoper %d has died\033[0m\n", time_in_ms, i + 1);
		pthread_mutex_unlock(element->info->print);
		return (1);
	}
	return (0);
}

int	is_alive(t_philo *ptr, struct timeval current_time, unsigned long time_die)
{
	unsigned long	total_difference;
	unsigned long	difference_seconds;
	unsigned long	difference_microseconds;

	if (current_time.tv_usec < ptr->time.tv_usec)
	{
		difference_seconds = (current_time.tv_sec - 1) - ptr->time.tv_sec;
		difference_microseconds = (current_time.tv_usec + 1000000)
			- ptr->time.tv_usec;
	}
	else
	{
		difference_seconds = current_time.tv_sec - ptr->time.tv_sec;
		difference_microseconds = current_time.tv_usec - ptr->time.tv_usec;
	}
	total_difference = difference_seconds * 1000 + difference_microseconds
		/ 1000;
	if (difference_microseconds % 1000 > 500)
		total_difference += 1;
	if (total_difference > time_die)
	{
		pthread_mutex_lock(ptr->info->terminate_lock);
		ptr->info->terminate_threads = 1;
		pthread_mutex_unlock(ptr->info->terminate_lock);
		return (1);
	}
	return (0);
}
