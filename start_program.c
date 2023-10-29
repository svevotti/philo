#include "philo.h"
#include <stdio.h>
#include <pthread.h>


// typedef struct s_single_philo {
// 	int philosopher;
// 	int	action;
// } 	t_single_philo;

void	think_life(t_philo *ptr)
{
	printf("philosopher %d is thinking\n", ptr->philo);
	// ptr->action = 1;
	sleep(1);
}

void	take_a_nap(t_philo *ptr)
{
	printf("philosopher %d is sleeping\n", ptr->philo);
	
	sleep(1);
}

void eat_spaghetti(t_philo *ptr)
{
	pthread_mutex_lock(ptr->fork_1);
	pthread_mutex_lock(ptr->fork_2);
	printf("philosopher %d is eating spaghetti\n", ptr->philo);
	sleep(1);
	// sleep(ptr->time_to_eat);
	pthread_mutex_unlock(ptr->fork_1);
	pthread_mutex_unlock(ptr->fork_2);
}

void	*routine(void *param)
{
	t_philo *ptr;

	ptr = (t_philo *)param;
	while (1) {
		// pthread_mutex_lock(ptr->fork_1);
		// pthread_mutex_lock(ptr->fork_2);
		// printf("thread %d is in the function\n", ptr->philo);
		// pthread_mutex_unlock(ptr->fork_1);
		// pthread_mutex_unlock(ptr->fork_2);
		eat_spaghetti(ptr);
		think_life(ptr);
		take_a_nap(ptr);
		sleep(1);
	}
	return NULL;
}

void create_threads(int count, int *finished)
{
	pthread_t	thread;
	t_philo		*philosopher;
	int			index;
	pthread_mutex_t *last_fork;

	index = 0;
	last_fork = malloc(sizeof(pthread_mutex_t));
	last_fork = NULL;
	while (index < count)
	{
		philosopher = (t_philo *)malloc(sizeof(t_philo));
		philosopher->philo = index;
		philosopher->finished = finished;
		if (last_fork == NULL)
		{
			philosopher->fork_1 = malloc(sizeof(pthread_mutex_t));
			pthread_mutex_init(philosopher->fork_1, NULL);
		}
		else
			philosopher->fork_1 = last_fork;
		philosopher->fork_2 = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philosopher->fork_2, NULL);
		last_fork = philosopher->fork_2;
		pthread_create(&thread, NULL, routine, philosopher);
		index++;
	}
}