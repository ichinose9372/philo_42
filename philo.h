/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:42 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/02 12:27:54 by yichinos         ###   ########.fr       */
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
	struct s_moniter	*moniter;
	int					eat_count;
	pthread_mutex_t		eat_mutex;
	long				start_eat;
	pthread_mutex_t		start_mutex;
	long				last_eat;
	pthread_mutex_t		last_mutex;
}	t_data;

typedef struct s_moniter
{
	t_data			**data;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				must_eat;
	pthread_t		pid;
	int				stop_flag;
	pthread_mutex_t	flag_mutex;
	int				philo_count;
}	t_moniter;

//check_arg
int		ft_digit(char *str);
t_data	**check_args_and_malloc(int argc, char **argv, t_data **data);
//init_data
void	init_data(char **argv, t_data **data, t_moniter *monu);
void	set_moniter(t_moniter *moniter, t_data **main, char **argv);

//set_time
long	cal_time(struct timeval time, struct timeval now);
long	get_now_time(void);

#endif


