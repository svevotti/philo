#include "philo.h"
#include <stdio.h>
#include <pthread.h>

void	think_life(t_philo *ptr)
{
	printf("philosopher %d is thinking\n", ptr->index);
}

void	take_a_nap(t_philo *ptr)
{
	printf("philosopher %d is sleeping\n", ptr->index);
	usleep(ptr->info->time_to_sleep * 1000);
}

void eat_spaghetti(t_philo *ptr)
{	
	pthread_mutex_lock(ptr->right_fork);
	pthread_mutex_lock(ptr->left_fork);
	printf("philosopher %d has taken a fork\n", ptr->index);
	ptr->status = EATING;
	printf("fork right %p - fork left %p\n", ptr->right_fork, ptr->left_fork);
	printf("philosopher %d is eating\n", ptr->index);
	usleep(ptr->info->time_to_eat * 1000);
	gettimeofday(&(ptr->time), NULL);
	// printf("last ate %lu\n", ptr->time.tv_sec);
	pthread_mutex_unlock(ptr->left_fork);
	pthread_mutex_unlock(ptr->right_fork);
	ptr->status = NOT_EATING;
}

void	*routine(void *param)
{
	t_philo *ptr;

	ptr = (t_philo *)param;
	while (1) {
		eat_spaghetti(ptr);
		take_a_nap(ptr);
		think_life(ptr);
		// usleep(1000000000);
	}
	return NULL;
}

void create_threads(t_info *info, t_philo **array)
{
	pthread_t	thread;
	t_philo		*ptr;
	int			index;
	pthread_mutex_t *temp_right_fork;

	index = 0;
	temp_right_fork = NULL;
	while (index < info->n_philo)
	{
		ptr = (t_philo *)malloc(sizeof(t_philo));
		gettimeofday(&(ptr->time), NULL);
		ptr->status = NOT_EATING;
		ptr->index = index;
		if (temp_right_fork)
			ptr->right_fork = temp_right_fork;
		ptr->left_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(ptr->left_fork, NULL);
		temp_right_fork = ptr->left_fork;
		if (info->n_philo == index + 1)
			array[0]->right_fork = temp_right_fork;
		ptr->info = info;
		array[index] = ptr;
		index++;
	}
	index = 0;
	while (index < info->n_philo)
	{
		pthread_create(&thread, NULL, routine, array[index]);
		index++;
	}
}