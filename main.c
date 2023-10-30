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

int	main(int argc, char **argv)
{
	t_philo	ptr;
	t_philo **array;
	int	time;

	if (argc == 2)
	{
		

		// ptr.n_forks = ptr.n_philos;
		// ptr.time_to_die = ft_atoi(argv[2]);
		// ptr.time_to_eat = ft_atoi(argv[3]);
		// ptr.time_to_sleep = ft_atoi(argv[4]);
		// if (check_argv(ptr) == 0)
		// 	printf("Error, something is missing or you just didn't understand the assigment!\n");
		printf("Parent is starting\n");
		array = (t_philo **)malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
		create_threads(ft_atoi(argv[1]), array);
		int count = 0;
		while (count <  ft_atoi(argv[1]))
		{
			printf("%d\n", array[count]->philo);
			count++;
		}
		exit(0);
		while (1)
		{
			printf("parent is checking\n");

			if (ptr.time.tv_sec < time)
				break ;
			usleep(1000000);
		}
		printf("parent is done\n");
	}
	else
		printf("Error, something is missing or you just didn't understand the assigment!\n");
	return (0);
}