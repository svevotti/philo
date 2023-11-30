#include "philo.h"

int	find_multi(const char *str);
int	find_digits(const char *str);

int	ft_atoi(const char *str)
{
	int	digit;
	int	m;
	int	number;

	m = find_multi(str);
	if (m == 0)
		return (0);
	number = 0;
	while (*str != '\0')
	{
		number = number + (*str - '0') * m;
		str++;
		m /= 10;
	}
	return (number);
}

int	find_digits(const char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			count++;
		else
			return (0);
		str++;
	}
	return (count);
}

int	find_multi(const char *str)
{
	int	digits;
	int	m;

	digits = find_digits(str);
	if (digits == 0)
		return (0);
	else
		digits -= 1;
	m = 1;
	while (digits > 0)
	{
		m *= 10;
		digits--;
	}
	return (m);
}
