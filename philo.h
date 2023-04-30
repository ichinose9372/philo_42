/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:42 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/30 14:54:34 by yichinos         ###   ########.fr       */
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
	int					num_philo;
	pthread_t			pid;
	pthread_mutex_t		fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct timeval		time;
	struct s_moniter	*moniter;
	int					count;
	int					flag;
}	t_data;

typedef struct s_moniter
{
	t_data			**data;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				must_eat;
	pthread_t		pid;
	struct timeval	moniter_time;
	pthread_mutex_t	mutex;
}	t_moniter;

//check_arg
int	ft_digit(char *str);
int p_atoi(char *str);

#endif


