#include "philo.h"

t_philo	**fill_info(t_info *ptr, char **argv, int argc);
int		get_time_s(t_philo **array, t_info *info);
int		check_status(t_philo *element, struct timeval time_stamp,
			int i, int *count_done_eating);
int		is_alive(t_philo *ptr, struct timeval current_time,
			unsigned long time_die);

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
			return (1);
		}
		while (1)
		{
			if (get_time_s(array, &info) == 1 || get_time_s(array, &info) == 2)
			{
				free_array(array, info.n_philo);
				return (1);
			}
			usleep(5000);
		}
	}
	else
		printf("Error, something went wrong!\n");
}

t_philo	**fill_info(t_info *ptr, char **argv, int argc)
{
	t_philo	**array;

	if (argc == 6)
		ptr->count_max_eat = ft_atoi(argv[5]);
	else
		ptr->count_max_eat = -1;
	ptr->n_philo = ft_atoi(argv[1]);
	ptr->time_to_die = ft_atoi(argv[2]);
	ptr->time_to_eat = ft_atoi(argv[3]);
	ptr->time_to_sleep = ft_atoi(argv[4]);
	array = (t_philo **)malloc(sizeof(t_philo *) * ptr->n_philo);
	if (array == NULL)
		return (NULL);
	return (array);
}

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
			return (1);
		i++;
	}
	if (count_done_eating == info->n_philo)
		return (2);
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
