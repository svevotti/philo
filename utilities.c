#include "philo.h"

int	ft_skip_spaces(char *str, int i)
{
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
	{
		i++;
	}
	return (i);
}

int	ft_check_sign(char *str, int i, int *sign)
{
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = *sign * (-1);
		i++;
	}
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	digit;
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	i = ft_skip_spaces(str, 0);
	i = ft_check_sign(str, i, &sign);
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			digit = str[i] - 48;
			number = number * 10 + digit;
		}
		else
			return (ERROR_NUMBER);
		i++;
	}
	if (number == 0)
		return (ERROR_NUMBER);
	if (sign == -1)
		return (ERROR_NUMBER);
	return (number);
}

int	check_argv(t_info *ptr, int argc)
{
	if (ptr->n_philo == -1)
		return (-1);
	else if (ptr->time_to_die == -1)
		return (-1);
	else if (ptr->time_to_eat == -1)
		return (-1);
	else if (ptr->time_to_sleep == -1)
		return (-1);
	if (argc == 6)
	{
		if (ptr->count_max_eat == -1)
			return (-1);
	}
	return (0);
}

void	free_array(t_philo **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]->left_fork);
		free(array[i]);
		i++;
	}
	free(array);
}
