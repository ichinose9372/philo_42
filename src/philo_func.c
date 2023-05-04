/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:21:39 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/04 16:35:34 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	flag_check(t_moniter *moniter)
{
	pthread_mutex_lock(&moniter->flag_mutex);
	if (moniter->stop_flag)
	{
		pthread_mutex_unlock(&moniter->flag_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&moniter->flag_mutex);
		return (0);
	}
}

void	philo_eat_left(t_data *data, t_moniter *moniter)
{
	pthread_mutex_lock(data->left_fork);
	pthread_mutex_lock(data->right_fork);
	print_status(data, moniter, 1);
	pthread_mutex_lock(&data->start_mutex);
	data->start_eat = get_now_time();
	pthread_mutex_unlock(&data->start_mutex);
	print_status(data, moniter, 2);
	pthread_mutex_lock(&data->eat_mutex);
	data->eat_count++;
	ft_usleep(data->start_eat, moniter->t_eat);
	pthread_mutex_unlock(&data->eat_mutex);
	pthread_mutex_unlock(data->right_fork);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_lock(&data->last_mutex);
	data->last_eat = get_now_time();
	pthread_mutex_unlock(&data->last_mutex);
}

void	philo_eat_right(t_data *data, t_moniter *moniter)
{
	pthread_mutex_lock(data->right_fork);
	pthread_mutex_lock(data->left_fork);
	print_status(data, moniter, 1);
	pthread_mutex_lock(&data->start_mutex);
	data->start_eat = get_now_time();
	pthread_mutex_unlock(&data->start_mutex);
	print_status(data, moniter, 2);
	pthread_mutex_lock(&data->eat_mutex);
	data->eat_count++;
	ft_usleep(data->start_eat, moniter->t_eat);
	pthread_mutex_unlock(&data->eat_mutex);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	pthread_mutex_lock(&data->last_mutex);
	data->last_eat = get_now_time();
	pthread_mutex_unlock(&data->last_mutex);
}

void	philo_sleep(t_data *data, t_moniter *moniter)
{
	print_status(data, moniter, 3);
	ft_usleep(data->last_eat, moniter->t_sleep);
}

void	*philo_func(void *arg)
{
	t_data			*data;
	t_moniter		*moniter;

	data = (t_data *)arg;
	moniter = data->moniter;
	while (1)
	{
		print_status(data, moniter, 0);
		if (data->num_philo % 2 == 1)
		{
			philo_eat_right(data, moniter);
			if (flag_check(moniter))
				break ;
			philo_sleep(data, moniter);
		}
		else
		{
			philo_eat_left(data, moniter);
			if (flag_check(moniter))
				break ;
			philo_sleep(data, moniter);
		}
	}
	pthread_exit(NULL);
}
