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

void	think_life(t_philo *ptr)
{
	unsigned long	time_stamp_ms;

	if (ptr->info->flag_teminate_threads == 0)
	{
		time_stamp_ms = get_time_stamp();
		printf("%lu philosopher %d is thinking\n", time_stamp_ms, ptr->index);
	}
}

void	take_a_nap(t_philo *ptr)
{
	unsigned long	time_stamp_ms;

	if (ptr->info->flag_teminate_threads == 0)
	{
		time_stamp_ms = get_time_stamp();
		printf("%lu philosopher %d is sleeping\n", time_stamp_ms, ptr->index);
		usleep(ptr->info->time_to_sleep * 1000);
	}
}

int	eat_spaghetti(t_philo *ptr)
{
	unsigned long	time_stamp_ms;

	if (ptr->count_done_eating == ptr->info->count_max_eat)
		ptr->least_eating_status = DONE_EATING;
	if (ptr->right_fork == NULL)
		return (1);
	if (pthread_mutex_lock(ptr->right_fork) != 0) {
		return (1);
	}
	if (pthread_mutex_lock(ptr->left_fork) != 0)
		return (1);
	time_stamp_ms = get_time_stamp();
	if (ptr->info->flag_teminate_threads == 0)
		printf("%lu philosopher %d has taken a fork\n", time_stamp_ms, ptr->index);
	gettimeofday(&(ptr->time), NULL);
	ptr->status = EATING;
	time_stamp_ms = get_time_stamp();
	if (ptr->info->flag_teminate_threads == 0) {
		printf("%lu philosopher %d is eating\n", time_stamp_ms, ptr->index);
		usleep(ptr->info->time_to_eat * 1000);
	}
	ptr->count_done_eating++;
	if (pthread_mutex_unlock(ptr->left_fork) != 0)
		return (1);
	if (pthread_mutex_unlock(ptr->right_fork) != 0)
		return (1);
	ptr->status = NOT_EATING;
	return (0);
}
