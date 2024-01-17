/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:56:00 by smazzari          #+#    #+#             */
/*   Updated: 2024/01/12 14:56:01 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**fill_info(t_info *ptr, char **argv, int argc);

int	main(int argc, char **argv)
{
	t_philo			**array;
	t_info			info;

	if (argc == 5 || argc == 6)
	{
		array = fill_info(&info, argv, argc);
		if (array == NULL)
			return (1);
		if (create_threads(&info, array) == 1)
		{
			free_array(array, info.n_philo);
			return (1);
		}
		while (1)
		{
			int status = get_time_s(array, &info);
			if (status == DEAD_STATUS || status == STOP_ETING)
				return (1);
		}
		usleep(5000);
	}
	else
		printf("Error, something went wrong!\n");
	return (0);
}

t_philo	**fill_info(t_info *ptr, char **argv, int argc)
{
	t_philo	**array;

	ptr->n_philo = ft_atoi(argv[1]);
	ptr->time_to_die = ft_atoi(argv[2]);
	ptr->time_to_eat = ft_atoi(argv[3]);
	ptr->time_to_sleep = ft_atoi(argv[4]);
	// ptr->flag_teminate_threads = 0;
	if (argc == 6)
		ptr->count_max_eat = ft_atoi(argv[5]);
	else
		ptr->count_max_eat = -1;
	if (check_argv(ptr, argc) == -1)
		return (NULL);
	array = (t_philo **)malloc(sizeof(t_philo *) * ptr->n_philo);
	if (array == NULL)
		return (NULL);
	return (array);
}
