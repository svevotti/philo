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

void	do_action(long duration)
{
	long	timestamp;

	timestamp = get_time_stamp();
	while (get_time_stamp() - timestamp < duration)
		usleep(duration / 10);
}

void	print_action(t_info *info, int philo, char *str)
{
	unsigned long	time_stamp_ms;
	int				terminate_status;

	time_stamp_ms = get_time_stamp() - info->start_time_ms;
	pthread_mutex_lock(info->terminate_lock);
	terminate_status = info->terminate_threads;
	pthread_mutex_unlock(info->terminate_lock);
	if (terminate_status == 0 || ft_strncmp(str, "has died", 8) == 0)
	{
		if (ft_strncmp(str, "has died", 8) == 0)
		{
			pthread_mutex_lock(info->print);
			printf("\033[1;31m%lu philosopher %d %s\033[0m\n", time_stamp_ms,
				philo, str);
			pthread_mutex_unlock(info->print);
		}
		else
		{
			pthread_mutex_lock(info->print);
			printf("%lu philosopher %d %s\n", time_stamp_ms, philo, str);
			pthread_mutex_unlock(info->print);
		}
	}
}

void	free_array(t_philo **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(array[i]->right_fork);
		pthread_mutex_destroy(array[i]->status_lock);
		pthread_mutex_destroy(array[i]->least_status_lock);
		free(array[i]->right_fork);
		free(array[i]->status_lock);
		free(array[i]->least_status_lock);
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;
	int				subs;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (i < n)
	{
		if (p1[i] == '\0' && p2[i] == '\0')
			return (0);
		else if (p1[i] != p2[i])
		{
			subs = p1[i] - p2[i];
			return (subs);
		}
		i++;
	}
	return (0);
}

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
