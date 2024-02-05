/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:13:06 by smazzari          #+#    #+#             */
/*   Updated: 2024/01/14 17:13:09 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (sign == -1)
		return (ERROR_NUMBER);
	return (number);
}
