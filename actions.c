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

int	print_action(int terminate_threads, int philo, char *str)
{
	unsigned long	time_stamp_ms;

	time_stamp_ms = get_time_stamp();

	if (terminate_threads == 0)
	{
		printf("%lu philosopher %d %s\n", time_stamp_ms, philo, str);
		return (0);
	}
	return (1);
}

void	think_life(t_philo *ptr)
{
	print_action(ptr->info->terminate_threads, ptr->index, "is thinking");
}

void	take_a_nap(t_philo *ptr)
{
	print_action(ptr->info->terminate_threads, ptr->index, "is sleeping");
	if (ptr->info->terminate_threads == 0)
		usleep(ptr->info->time_to_sleep * 1000);
}

int	eat_spaghetti(t_philo *ptr)
{
	if (ptr->count_done_eating == ptr->info->count_max_eat)
		ptr->least_eating_status = DONE_EATING;
	if (ptr->right_fork == NULL)
		return (1);
	pthread_mutex_lock(ptr->right_fork);
	pthread_mutex_lock(ptr->left_fork);
	print_action(ptr->info->terminate_threads, ptr->index, "has taken a fork");
	gettimeofday(&(ptr->time), NULL);
	ptr->status = EATING;
	print_action(ptr->info->terminate_threads, ptr->index, "is eating");
	if (ptr->info->terminate_threads == 0)
		usleep(ptr->info->time_to_eat * 1000);
	ptr->count_done_eating++;
	pthread_mutex_unlock(ptr->left_fork);
	pthread_mutex_unlock(ptr->right_fork);
	ptr->status = NOT_EATING;
	return (0);
}
