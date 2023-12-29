#include <stdio.h>
#include <unistd.h>
#include "philo.h"

// int check_argv(t_philo ptr)
// {
// 	if (ptr.n_philos == 0)
// 		return (0);
// 	else if (ptr.time_to_die == 0)
// 		return (0);
// 	else if (ptr.time_to_eat == 0)
// 		return (0);
// 	else if (ptr.time_to_sleep == 0)
// 		return (0);
// 	return (1);
// }

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

void	fill_info(t_info *ptr, char **argv, int argc)
{
	if (argc == 6)
		ptr->count_max_eat = ft_atoi(argv[5]);
	else
		ptr->count_max_eat = -1;
	ptr->n_philo = ft_atoi(argv[1]);
	ptr->time_to_die = ft_atoi(argv[2]);
	ptr->time_to_eat = ft_atoi(argv[3]);
	ptr->time_to_sleep = ft_atoi(argv[4]);
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

int	main(int argc, char **argv)
{
	t_philo			**array;
	struct timeval	time;
	t_info			info;
	int				i;
	int				count_done_eating;

	if (argc == 5 || argc == 6)
	{
		fill_info(&info, argv, argc);
		array = (t_philo **)malloc(sizeof(t_philo *) * info.n_philo);
		if (array == NULL)
			return (1);
		create_threads(&info, array);
		while (1)
		{
			i = 0;
			count_done_eating = 0;
			gettimeofday(&time, NULL);
			while (i < info.n_philo)
			{
				if (check_status(array[i], time, i, &count_done_eating) == 1)
				{
					//free
					return (1);
				}
				i++;
			}
			if (count_done_eating == info.n_philo)
			{
				//free
				return (0);
			}
			usleep(5000);
		}
	}
	else
		printf("Error, something went wrong!\n");
	return (0);
}
