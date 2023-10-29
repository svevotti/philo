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
	int finished;

	if (argc == 2)
	{
		

		// ptr.n_forks = ptr.n_philos;
		// ptr.time_to_die = ft_atoi(argv[2]);
		// ptr.time_to_eat = ft_atoi(argv[3]);
		// ptr.time_to_sleep = ft_atoi(argv[4]);
		// if (check_argv(ptr) == 0)
		// 	printf("Error, something is missing or you just didn't understand the assigment!\n");
		printf("Parent is starting\n");
		finished = 0;
		create_threads(ft_atoi(argv[1]), &finished);
		while (1)
		{
			printf("parent is checking\n");
			if (finished == 1)
				break ;
			sleep(1);
		}
		printf("parent is done\n");
		// printf("%d, %d, %d, %d\n", ptr.n_philos, ptr.time_to_die, ptr.time_to_eat, ptr.time_to_sleep);
	}
	else
		printf("Error, something is missing or you just didn't understand the assigment!\n");
	return (0);
}