/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:55:55 by smazzari          #+#    #+#             */
/*   Updated: 2024/01/12 14:55:56 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo	*ptr;
	int		terminate_status;

	ptr = (t_philo *)param;
	while (1)
	{
		if (eat_spaghetti(ptr) != 0)
			return (NULL);
		take_a_nap(ptr);
		think_life(ptr);
		pthread_mutex_lock(ptr->info->terminate_lock);
		terminate_status = ptr->info->terminate_threads;
		pthread_mutex_unlock(ptr->info->terminate_lock);
		if (terminate_status == 1)
			return (NULL);
	}
	return (NULL);
}

t_philo	*create_philosopher(int index, pthread_mutex_t *fork, t_info *info)
{
	t_philo			*ptr;

	ptr = (t_philo *)malloc(sizeof(t_philo));
	if (ptr == NULL)
		return (NULL);
	gettimeofday(&(ptr->time), NULL);
	ptr->status = NOT_EATING;
	ptr->least_eating_status = NOT_DONE_EATING;
	ptr->count_done_eating = 0;
	ptr->index = index + 1;
	ptr->left_fork = fork;
	ptr->right_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (ptr->right_fork == NULL)
		return (NULL);
	if (pthread_mutex_init(ptr->right_fork, NULL) != 0)
		return (NULL);
	ptr->status_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ptr->status_lock, NULL);
	ptr->least_status_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ptr->least_status_lock, NULL);
	ptr->info = info;
	return (ptr);
}

int	create_threads(t_info *info, t_philo **array)
{
	t_philo			*ptr;
	int				index;
	pthread_mutex_t	*temp_left_fork;

	index = 0;
	temp_left_fork = NULL;
	while (index < info->n_philo)
	{
		ptr = create_philosopher(index, temp_left_fork, info);
		if (ptr == NULL)
			return (1);
		temp_left_fork = ptr->right_fork;
		if (info->n_philo == index + 1 && info->n_philo > 1)
			array[0]->left_fork = temp_left_fork;
		array[index] = ptr;
		index++;
	}
	index = 0;
	while (index < info->n_philo)
	{
		ptr = array[index++];
		if (pthread_create(&(ptr->thread), NULL, routine, ptr) != 0)
			return (1);
	}
	return (0);
}
