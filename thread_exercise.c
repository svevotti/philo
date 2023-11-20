#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//create a program that use two threads to sum two number to reach 100 where first
//number calculate first half;

typedef struct s_sum {
	int sum;
	int	a;
	int b;
	int i;
	int count_a;
	int count_b;
	int	check_a;
	int	check_b;
	pthread_mutex_t lock;
} t_sum;

void	initialize_variables(t_sum *number)
{
	number->sum = 0;
	number->a = 1;
	number->b = 1;
	number->i = 0;
	number->count_a = 0;
	number->count_b = 0;
	number->check_a = 3;
	number->check_b = 3;

}

void	*sum_op(void *param)
{
	t_sum *number;
	int i = 0;

	number = (t_sum *)param;
	while (i < 10000000)
	{
		pthread_mutex_lock(&number->lock);
		// number->sum = number-> sum + 1;
		if (number->sum < 5000000)
		{
			number->sum = number->sum + number->a;
			number->count_a++;
			number->check_a = 1;
		}
		else
		{
			number->sum = number->sum + number->b;
			number->count_b++;
			number->check_b = 2;
		}
		pthread_mutex_unlock(&number->lock);
		i += 1;	
	}

	return (NULL);
}

int main(void)
{
	pthread_t	tid_1;
	pthread_t	tid_2;
	t_sum		number;


	initialize_variables(&number);
	pthread_mutex_init(&number.lock, NULL);
	pthread_create(&tid_1, NULL, sum_op, &number);
	pthread_create(&tid_2, NULL, sum_op, &number);
	pthread_join(tid_1, NULL);
	printf("thread %d is done\n", number.check_a);
	pthread_join(tid_2, NULL);
	printf("thread %d is done\n", number.check_b);
	printf("final sum %d for count a %d and count %d\n", number.sum, number.count_a, number.count_b);
	printf("program ends\n");
}