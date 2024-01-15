/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:56:21 by smazzari          #+#    #+#             */
/*   Updated: 2024/01/12 14:56:22 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argv(t_info *ptr, int argc)
{
	if (ptr->n_philo == -1)
		return (-1);
	else if (ptr->time_to_die == -1)
		return (-1);
	else if (ptr->time_to_eat == -1)
		return (-1);
	else if (ptr->time_to_sleep == -1)
		return (-1);
	if (argc == 6)
	{
		if (ptr->count_max_eat == -1)
			return (-1);
	}
	return (0);
}

int	check_philo_status(t_philo **array, t_info *info)
{
	int	time_death;
	// int	i;

	// i = 0;
	time_death = get_time_s(array, info);
	if (time_death == 1 || time_death == 2)
	{
		info->flag_terminate_thread = 1;
		// while (i < info->n_philo && info->n_philo > 1)
		// {
		// 	// printf("i %d\n", i);
		// 	pthread_join(array[i]->thread, NULL);
		// 	i++;
		// }
		free_array(array, info->n_philo);
		pthread_mutex_destroy(info->mutex);
		return (1);
	}
	return (0);
}

void	free_array(t_philo **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(array[i]->left_fork);
		free(array[i]->left_fork);
		free(array[i]);
		i++;
	}
	free(array);
}
