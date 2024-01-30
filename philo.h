/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazzari <smazzari@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:56:11 by smazzari          #+#    #+#             */
/*   Updated: 2024/01/12 14:56:13 by smazzari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR_NUMBER -1

# define EATING 0
# define NOT_EATING 1

# define DONE_EATING 0
# define NOT_DONE_EATING 1

# define DEAD 1
# define STOP_EATING 2

typedef struct s_info {
	int	n_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_think;
	int	count_max_eat;
	int	terminate_threads;
	pthread_mutex_t	*print;
}				t_info;

typedef struct s_philo {
	int				index;
	struct timeval	time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
	int				status;
	int				least_eating_status;
	int				count_done_eating;
	pthread_t		thread;
}				t_philo;			

//intit program
int		create_threads(t_info *info, t_philo **array);

//utilities
void	free_array(t_philo **array, int size);
int		check_argv(t_info *ptr, int argc);

//ft_atoi
int		ft_atoi(char *str);

//actions
void	think_life(t_philo *ptr);
void	take_a_nap(t_philo *ptr);
int		eat_spaghetti(t_philo *ptr);

//get_time_stamp
int		get_time_s(t_philo **array, t_info *info);

#endif
