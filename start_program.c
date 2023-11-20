#include "philo.h"
#include <stdio.h>
#include <pthread.h>


float	convert_in_milliseconds(int time)
{
	float	time_ms;

	time_ms = time / (float)1000;
	return (time_ms);
}

void	think_life(t_philo *ptr)
{
	printf("philosopher %d is thinking\n", ptr->index);
	usleep(1000000);
}

void	take_a_nap(t_philo *ptr)
{
	struct timeval time_1;
	struct timeval time_2;

	gettimeofday(NULL, &time_1);
	printf("philosopher %d is sleeping\n", ptr->index);
	usleep(200);
	gettimeofday(NULL, &time_2);

	sleep(1);
}

void eat_spaghetti(t_philo *ptr)
{	
	pthread_mutex_lock(ptr->fork_1);
	pthread_mutex_lock(ptr->fork_2);
	usleep(1000000);
	gettimeofday(&(ptr->time), NULL);
	printf("last ate %lu\n", ptr->time.tv_sec);
	pthread_mutex_unlock(ptr->fork_1);
	pthread_mutex_unlock(ptr->fork_2);
}

void	*routine(void *param)
{
	t_philo *ptr;

	ptr = (t_philo *)param;
	while (1) {
		eat_spaghetti(ptr);
		usleep(1000000);
	}
	return NULL;
}

void create_threads(t_info *info, t_philo **array)
{
	pthread_t	thread;
	t_philo		*ptr;
	int			index;
	pthread_mutex_t *last_fork;

	index = 0;
	last_fork = malloc(sizeof(pthread_mutex_t));
	last_fork = NULL;
	while (index < info->n_philo)
	{
		ptr = (t_philo *)malloc(sizeof(t_philo));
		gettimeofday(&(ptr->time), NULL);
		ptr->index = index;
		if (last_fork == NULL)
		{
			ptr->fork_1 = malloc(sizeof(pthread_mutex_t));
			pthread_mutex_init(ptr->fork_1, NULL);
		}
		else
			ptr->fork_1 = last_fork;
		ptr->fork_2 = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(ptr->fork_2, NULL);
		last_fork = ptr->fork_2;
		ptr->info = info;
		pthread_create(&thread, NULL, routine, ptr);
		array[index] = ptr;
		index++;
	}
}