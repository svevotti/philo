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

int	check_philo_status(t_philo **array, t_info info)
{
	int	time_death;

	time_death = get_time_s(array, &info);
	if (time_death == 1 || time_death == 2)
	{
		free_array(array, info.n_philo);
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
		free(array[i]->left_fork);
		free(array[i]);
		i++;
	}
	free(array);
}
