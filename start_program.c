#include "philo.h"
#include <stdio.h>
#include <pthread.h>

// typedef struct s_single_philo {
// 	int philosopher;
// 	int	action;
// } 	t_single_philo;

// void	think_life(t_philo *ptr)
// {
// 	printf("philosopher %d is thinking\n", ptr->index);
// 	ptr->action = 1;
// 	sleep(4);
// }

// void	take_a_nap(t_philo *ptr)
// {
// 	printf("philosopher %d is sleeping\n", ptr->index);
// 	ptr->action = 3;
// 	sleep(ptr->time_to_sleep);
// }

// void eat_spaghetti(t_philo *ptr)
// {
// 	if (ptr->i == 1)
// 		sleep(1);
// 	ptr->i = 0;
// 	pthread_mutex_lock(&ptr->lock);
// 	printf("philosopher %d is eating spaghetti\n", ptr->index);
// 	sleep(ptr->time_to_eat);
// 	pthread_mutex_unlock(&ptr->lock);
// }

void	*routine(void *param)
{
	t_philo *ptr;

	ptr = (t_philo *)param;
	// pthread_mutex_lock(&ptr->lock);
	// while (1)
	// {
	printf("thread is in the function %d\n", ptr->philo);
	// pthread_mutex_unlock(&ptr->lock);
	// sleep(1);
	// }
	// eat_spaghetti(ptr);
	// take_a_nap(ptr);
	// ptr->action = 10;
	return NULL;
}

void create_threads(int count, int *finished)
{
	pthread_t	thread;
	t_philo		*philosopher;
	int			index;

	// ptr->time_to_think = ptr->time_to_die - ptr->time_to_eat - ptr->time_to_sleep;
	// ptr->action = 0;
	// ptr->index = 0;
	// pthread_mutex_init(&ptr->lock, NULL);
	// tid = (pthread_t *)malloc(sizeof(pthread_t) * tot_thread);
	index = 0;
	while (index < count)
	{
		// ptr->index = index + 1;
	// printf("%d, %d, %d, %d\n", ptr->n_philos, ptr->time_to_die, ptr->time_to_eat, ptr->time_to_sleep);
		philosopher = (t_philo *)malloc(sizeof(t_philo));
		philosopher->philo = index;
		philosopher->finished = finished;
		pthread_create(&thread, NULL, routine, philosopher);
		index++;
		pthread_join(thread, NULL);
		// sleep(5);
		// tot_thread--;
	}
	// sleep(20);
}