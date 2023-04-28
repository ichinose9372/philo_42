/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:42 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/28 22:07:48 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
	int				num_philo;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				must_eat;
	pthread_t		pid;
	pthread_mutex_t	fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	time;
	struct timeval	last_eat;
}	t_data;
//check_arg
int	ft_digit(char *str);
int p_atoi(char *str);

#endif


