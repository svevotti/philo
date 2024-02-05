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
#include <string.h>

void	do_action(long duration)
{
	long timestamp = get_time_stamp();

	while (get_time_stamp() - timestamp < duration)
			usleep(duration / 10);
}

void	print_action(t_info *info, int philo, char *str)
{
	unsigned long	time_stamp_ms;
	int terminate_status;

	time_stamp_ms = get_time_stamp() - info->start_time_ms;
	pthread_mutex_lock(info->terminate_lock);
	terminate_status = info->terminate_threads;
	pthread_mutex_unlock(info->terminate_lock);
	if (terminate_status == 0 || strcmp(str, "has died") == 0)
	{
		if (strcmp(str, "has died") == 0)
		{
			pthread_mutex_lock(info->print);
			printf("\033[1;31m%lu philosopher %d %s\033[0m\n", time_stamp_ms, philo, str);
			pthread_mutex_unlock(info->print);
		}
		else {
			pthread_mutex_lock(info->print);
			printf("%lu philosopher %d %s\n", time_stamp_ms, philo, str);
			pthread_mutex_unlock(info->print);
		}
	}
}

void	take_a_nap(t_philo *ptr)
{
	int terminate_status;

	print_action(ptr->info, ptr->index, "is sleeping");
	pthread_mutex_lock(ptr->info->terminate_lock);
	terminate_status = ptr->info->terminate_threads;
	pthread_mutex_unlock(ptr->info->terminate_lock);
	if (terminate_status == 0)
		do_action(ptr->info->time_to_sleep);
}

void	get_forks(t_philo *philo)
{
	if (philo->index == philo->info->n_philo - 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (philo->index == philo->info->n_philo && philo->count_done_eating % 2 == 1)
			usleep(100);
		pthread_mutex_lock(philo->left_fork);	
	}
}

void	give_back_forks(t_philo *philo)
{
		pthread_mutex_unlock(philo->right_fork);	
		pthread_mutex_unlock(philo->left_fork);
}

int	eat_spaghetti(t_philo *ptr)
{
	int terminate_status;

	if (ptr->count_done_eating == ptr->info->count_max_eat) {
		pthread_mutex_lock(ptr->least_status_lock);
		ptr->least_eating_status = DONE_EATING;
		pthread_mutex_unlock(ptr->least_status_lock);
	}
	if (ptr->left_fork == NULL)
		return (1);
	get_forks(ptr);
	print_action(ptr->info, ptr->index, "has taken a fork");
	pthread_mutex_lock(ptr->status_lock);
	ptr->status = EATING;
	ptr->count_done_eating++;
	ptr->time_beginning_eating = get_time_stamp();
	pthread_mutex_unlock(ptr->status_lock);
	pthread_mutex_lock(ptr->info->terminate_lock);
	terminate_status = ptr->info->terminate_threads;
	pthread_mutex_unlock(ptr->info->terminate_lock);
	print_action(ptr->info, ptr->index, "is eating");
	if (terminate_status == 0)
		do_action(ptr->info->time_to_eat);
	give_back_forks(ptr);
	pthread_mutex_lock(ptr->status_lock);
	ptr->status = NOT_EATING;
	pthread_mutex_unlock(ptr->status_lock);
	return (0);
}
