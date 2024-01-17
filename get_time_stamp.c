#include "philo.h"

int		check_status(t_philo *element, struct timeval time_stamp,
			int i, int *count_done_eating);
int		is_alive(t_philo *ptr, struct timeval current_time,
			unsigned long time_die);

int	get_time_s(t_philo **array, t_info *info)
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
			return (DEAD_STATUS);
		i++;
	}
	if (count_done_eating == info->n_philo)
		return (STOP_ETING);
	return (0);
}

int	check_status(t_philo *element, struct timeval time_stamp,
					int i, int *count_done_eating)
{
	unsigned long	time_in_ms;

	if (element->least_eating_status == DONE_EATING)
		*count_done_eating = *count_done_eating + 1;
	if (element->status == NOT_EATING
		&& is_alive(element, time_stamp, element->info->time_to_die) == DEAD)
	{
		time_in_ms = time_stamp.tv_sec * 1000 + time_stamp.tv_usec / 1000;
		printf("%lu philosoper %d has died\n", time_in_ms, i + 1);
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
	if (total_difference > time_die)
		return (1);
	return (0);
}
