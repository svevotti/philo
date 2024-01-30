/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:55:46 by smazzari          #+#    #+#             */
/*   Updated: 2024/01/12 14:55:47 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time_stamp(void)
{
	struct timeval	time_stamp;
	unsigned long	time_stamp_ms;

	gettimeofday(&time_stamp, NULL);
	time_stamp_ms = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	if (time_stamp.tv_usec % 1000 > 500)
		time_stamp_ms += 1;
	return (time_stamp_ms);
}

int	print_action(t_info *info, int philo, char *str)
{
	unsigned long	time_stamp_ms;
	int terminate_status;

	time_stamp_ms = get_time_stamp();
	pthread_mutex_lock(info->terminate_lock);
	terminate_status = info->terminate_threads;
	pthread_mutex_unlock(info->terminate_lock);
	if (terminate_status == 0)
	{
		pthread_mutex_lock(info->print);
		printf("%lu philosopher %d %s\n", time_stamp_ms, philo, str);
		pthread_mutex_unlock(info->print);
		return (0);
	}
	return (1);
}

void	think_life(t_philo *ptr)
{
	print_action(ptr->info, ptr->index, "is thinking");
}

void	take_a_nap(t_philo *ptr)
{
	int terminate_status;

	print_action(ptr->info, ptr->index, "is sleeping");
	pthread_mutex_lock(ptr->info->terminate_lock);
	terminate_status = ptr->info->terminate_threads;
	pthread_mutex_unlock(ptr->info->terminate_lock);
	if (terminate_status == 0)
		usleep(ptr->info->time_to_sleep * 1000);
}

int	eat_spaghetti(t_philo *ptr)
{
	int terminate_status;

	if (ptr->count_done_eating == ptr->info->count_max_eat) {
		pthread_mutex_lock(ptr->least_status_lock);
		ptr->least_eating_status = DONE_EATING;
		pthread_mutex_unlock(ptr->least_status_lock);
	}
	if (ptr->right_fork == NULL)
		return (1);
	if (ptr->index == ptr->info->n_philo)
	{
		pthread_mutex_lock(ptr->right_fork);
		pthread_mutex_lock(ptr->left_fork);
	}
	else
	{
		pthread_mutex_lock(ptr->left_fork);
		pthread_mutex_lock(ptr->right_fork);
	}
	print_action(ptr->info, ptr->index, "has taken a fork");
	gettimeofday(&(ptr->time), NULL);
	pthread_mutex_lock(ptr->status_lock);
	ptr->status = EATING;
	pthread_mutex_unlock(ptr->status_lock);
	print_action(ptr->info, ptr->index, "is eating");
	pthread_mutex_lock(ptr->info->terminate_lock);
	terminate_status = ptr->info->terminate_threads;
	pthread_mutex_unlock(ptr->info->terminate_lock);
	if (terminate_status == 0)
		usleep(ptr->info->time_to_eat * 1000);
	ptr->count_done_eating++;
	pthread_mutex_unlock(ptr->left_fork);
	pthread_mutex_unlock(ptr->right_fork);
	pthread_mutex_lock(ptr->status_lock);
	ptr->status = NOT_EATING;
	pthread_mutex_unlock(ptr->status_lock);
	return (0);
}
