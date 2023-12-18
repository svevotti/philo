#include "philo.h"
#include <stdio.h>
#include <pthread.h>

void	think_life(t_philo *ptr)
{
	struct timeval time_stamp;
	unsigned long time_stamp_ms;

	gettimeofday(&time_stamp, NULL);
	time_stamp_ms = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	printf("%lu philosopher %d is thinking\n", time_stamp_ms, ptr->index);
}

void	take_a_nap(t_philo *ptr)
{
	struct timeval time_stamp;
	unsigned long time_stamp_ms;

	gettimeofday(&time_stamp, NULL);
	time_stamp_ms = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	printf("%lu philosopher %d is sleeping\n", time_stamp_ms,  ptr->index);
	usleep(ptr->info->time_to_sleep * 1000);
}

void eat_spaghetti(t_philo *ptr)
{	
	struct timeval time_stamp_fork;
	unsigned long time_stamp_ms;
	struct timeval time_stamp_eating;

	pthread_mutex_lock(ptr->right_fork);
	pthread_mutex_lock(ptr->left_fork);
	gettimeofday(&time_stamp_fork, NULL);
	time_stamp_ms = (time_stamp_fork.tv_sec * 1000) + (time_stamp_fork.tv_usec / 1000);
	// printf("reminder - %d for %d - div %d\n", time_stamp_fork.tv_usec % 1000, time_stamp_fork.tv_usec, time_stamp_fork.tv_usec / 1000);
	if (time_stamp_fork.tv_usec % 1000 > 500)
		time_stamp_ms += 1;
	printf("%lu philosopher %d has taken a fork\n", time_stamp_ms, ptr->index);
	gettimeofday(&(ptr->time), NULL);
	ptr->status = EATING;
	gettimeofday(&time_stamp_eating, NULL);
	time_stamp_ms = (time_stamp_eating.tv_sec * 1000) + (time_stamp_eating.tv_usec / 1000);
	if (time_stamp_eating.tv_usec % 1000 > 500)
		time_stamp_ms += 1;
	printf("%lu philosopher %d is eating\n", time_stamp_ms, ptr->index);
	usleep(ptr->info->time_to_eat * 1000);
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
		ptr->index = index + 1;
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