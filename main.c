/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:10:48 by smazzari          #+#    #+#             */
/*   Updated: 2024/01/16 14:10:52 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**fill_info(t_info *ptr, char **argv, int argc);
int		get_time_s(t_philo **array, t_info *info);
int		check_status(t_philo *element, struct timeval time_stamp,
			int *count_done_eating);
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
			pthread_mutex_destroy(info.mutex);
			free(info.mutex);
			free_array(array, info.n_philo);
			return (1);
		}
		while (1)
		{
			if (check_philo_status(array, &info) == 1)
			{
				free(info.mutex);
				return (1);
			}
		}
		usleep(5000);
	}
	else
		printf("Error, something went wrong!\n");
	return (0);
}

t_philo	**fill_info(t_info *ptr, char **argv, int argc)
{
	t_philo	**array;

	ptr->n_philo = ft_atoi(argv[1]);
	ptr->time_to_die = ft_atoi(argv[2]);
	ptr->time_to_eat = ft_atoi(argv[3]);
	ptr->time_to_sleep = ft_atoi(argv[4]);
	ptr->flag_terminate_thread = 0;
	ptr->mutex = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(ptr->mutex, NULL) != 0)
		return (NULL);
	if (argc == 6)
		ptr->count_max_eat = ft_atoi(argv[5]);
	else
		ptr->count_max_eat = -1;
	if (check_argv(ptr, argc) == -1)
		return (NULL);
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
		if (check_status(array[i], time, &count_done_eating) == 1)
		{
			safe_print("has died", info->mutex,
				info->flag_terminate_thread, info->n_philo);
			return (1);
		}
		i++;
	}
	if (count_done_eating == info->n_philo)
	{
		return (2);
	}
	return (0);
}

int	check_status(t_philo *element, struct timeval time_stamp,
		int *count_done_eating)
{
	if (element->least_eating_status == DONE_EATING)
		*count_done_eating = *count_done_eating + 1;
	if (element->status == NOT_EATING
		&& is_alive(element, time_stamp, element->info->time_to_die) == DEAD)
		return (1);
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
