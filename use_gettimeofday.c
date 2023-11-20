#include <sys/time.h>
#include <stdio.h>
# include <unistd.h>

int main(void)
{
	struct timeval time_after_eating;
	struct timeval time_before_eating_again;

	while (1)
	{
		// gettimeofday(NULL, &time_after_eating);
		gettimeofday(&time_after_eating, NULL);
		printf("before sleep %ld - %d\n", time_after_eating.tv_sec, time_after_eating.tv_usec);
		sleep(1);
		// gettimeofday(NULL, &time_before_eating_again);
		// gettimeofday(&time_before_eating_again, NULL);
		// printf("before sleep %ld\n", time_before_eating_again.tv_sec);
		// sleep(1);
	}
}