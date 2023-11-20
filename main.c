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
	unsigned long difference;

	difference = (current_time.tv_sec) - ptr->time.tv_sec;
	printf("difference %lu - current time %lu - lsat ate %lu\n", difference, current_time.tv_sec, ptr->time.tv_sec);
	if (difference > time_die)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	// t_philo	info;
	t_philo **array;
	struct timeval	time;
	t_info info;
	// unsigned long e_msec;

	if (argc == 5)
	{
		info.n_philo = ft_atoi(argv[1]);
		info.time_to_die = ft_atoi(argv[2]);
		info.time_to_eat = ft_atoi(argv[3]);
		info.time_to_sleep = ft_atoi(argv[4]);
		// if (check_argv(ptr) == 0)
		// 	printf("Error, something is missing or you just didn't understand the assigment!\n");
		printf("Parent is starting\n");
		array = (t_philo **)malloc(sizeof(t_philo *) * info.n_philo);
		create_threads(&info, array);
		int i = 0;
		while (1)
		{
			printf("parent is checking\n");
			gettimeofday(&time, NULL);
			// e_msec = time.tv_sec * 1000;
			//printf("current time %lu\n", e_msec);
			while (i < info.n_philo)
			{
				if (is_alive(array[i], time, info.time_to_die) == 1)
					break ;
				i++;
			}
			i = 0;
			usleep(1000000);
		}
		printf("parent is done\n");
	}
	else
		printf("Error, something is missing or you just didn't understand the assigment!\n");
	return (0);
}