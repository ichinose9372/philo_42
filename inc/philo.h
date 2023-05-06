/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:45:42 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/06 10:42:44 by ichinoseyuu      ###   ########.fr       */
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
# include <string.h>

typedef struct s_data
{
	int					num_philo;
	pthread_t			pid;
	pthread_mutex_t		fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		start_mutex;
	pthread_mutex_t		last_mutex;
	struct s_moniter	*moniter;
	int					eat_count;
	long				start_eat;
	long				last_eat;
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
int			ft_digit(char *str);
int			check_args(int argc, char **argv);
int			philo_atoi(char *str);
//init_data
t_data		**malloc_data(int argc, char **argv);
int			init_data(char **argv, t_data **data, t_moniter *monu);
t_moniter	*make_moniter_init(t_data **main, char **argv);
//main func
void		philo(t_data **data, t_moniter *moniter, int num);
void		mutex_del(t_data **data, t_moniter *moniter, int num);
//moniter
int			moni_time_check(t_moniter *moniter, t_data *data);
int			moni_eat_count_check(t_moniter *moniter, t_data *data, int *num);
void		*moniter_func(void *arg);
//philo
int			flag_check(t_moniter *moniter);
void		philo_eat_left(t_data *data, t_moniter *moniter);
void		philo_eat_right(t_data *data, t_moniter *moniter);
void		philo_sleep(t_data *data, t_moniter *moniter);
void		*philo_func(void *arg);
//set_time
long		get_now_time(void);
void		ft_usleep(long start, long time_to);
//
void		free_data(t_data **data);
void		free_all(t_data **data, t_moniter *moniter);
void		print_status(t_data *data, t_moniter *moniter, int status);
//only_one
void		only_one(t_data *data);
void		*only_one_func(void *arg);
#endif
