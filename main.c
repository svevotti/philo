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

int	main(int argc, char **argv)
{
	t_philo			**array;
	struct timeval	time;
	t_info			info;
	unsigned long	time_stamp_ms;
	int				i;

	if (argc == 5)
	{
		info.n_philo = ft_atoi(argv[1]);
		info.time_to_die = ft_atoi(argv[2]);
		info.time_to_eat = ft_atoi(argv[3]);
		info.time_to_sleep = ft_atoi(argv[4]);
		array = (t_philo **)malloc(sizeof(t_philo *) * info.n_philo);
		create_threads(&info, array);
		i = 0;
		while (1)
		{
			gettimeofday(&time, NULL);
			while (i < info.n_philo)
			{
				if (array[i]->status == NOT_EATING
					&& is_alive(array[i], time, info.time_to_die) == DEAD)
				{
					gettimeofday(&time, NULL);
					printf("%lu philosoper %d has died\n", time_stamp_ms, i + 1);
					exit(0);
				}
				i++;
			}
			i = 0;
			usleep(5000);
		}
	}
	else
		printf("Error, something went wrong!\n");
	return (0);
}
