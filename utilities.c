/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:56:21 by smazzari          #+#    #+#             */
/*   Updated: 2024/01/12 14:56:22 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;
	int				subs;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (i < n)
	{
		if (p1[i] == '\0' && p2[i] == '\0')
			return (0);
		else if (p1[i] != p2[i])
		{
			subs = p1[i] - p2[i];
			return (subs);
		}
		i++;
	}
	return (0);
}
