#include "philo.h"

int		free_threads(t_philo **array, t_info *info);

void	free_info(t_info *info)
{
	pthread_mutex_destroy(info->print);
	pthread_mutex_destroy(info->terminate_lock);
	free(info->print);
	free(info->terminate_lock);
}

int	main(int argc, char **argv)
{
	t_philo			**array;
	t_info			info;

	if (argc == 5 || argc == 6)
	{
		array = fill_info(&info, argv, argc);
		if (array == NULL)
			return (1);
		if (create_threads(&info, array) == 1)
		{
			free_array(array, info.n_philo);
			free_info(&info);
			return (1);
		}
		while (1)
		{
			if (free_threads(array, &info) == 1)
				return (1);
			usleep(5);
		}
	}
	else
		printf("Error, something went wrong!\n");
	return (0);
}

int	free_threads(t_philo **array, t_info *info)
{
	int	status;
	int	i;

	i = 0;
	status = get_status(array, info);
	if (status == DEAD || status == STOP_EATING)
	{
		i = 0;
		while (i < info->n_philo)
		{
			pthread_join(array[i]->thread, NULL);
			i++;
		}
		free_array(array, info->n_philo);
		free_info(info);
		return (1);
	}
	return (0);
}
