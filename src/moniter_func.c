/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:22:02 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/04 10:20:00 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_check_frag(t_moniter *moniter, t_data *data)
{
	int	i;

	i = 0;
	while (i < moniter->philo_count)
	{
		pthread_mutex_lock(data->eat_count);
		if (data->eat_count == monitert->must_eat)
		{
			i++;
		}
		else
		{
			pthread_mutex_unlock(data->eat_count);
			return (0);
		}
	}
	return (1);
}

int	moni_time_check(t_moniter *moniter, t_data *data)
{
	pthread_mutex_lock(&data->start_mutex);
	pthread_mutex_lock(&data->last_mutex);
	if (moniter->t_die < data->start_eat - data->last_eat)
	{
		pthread_mutex_unlock(&data->start_mutex);
		pthread_mutex_unlock(&data->last_mutex);
		pthread_mutex_lock(&moniter->flag_mutex);
		moniter->stop_flag = 1;
		pthread_mutex_lock(&moniter->flag_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->start_mutex);
		pthread_mutex_unlock(&data->last_mutex);
	}
	return (0);
}

int	moni_eat_count_check(t_moniter *moniter, t_data *data)
{
	int		count;
	int		i;

	pthread_mutex_lock(&data->eat_mutex);
	if (data->eat_count >= moniter->must_eat)
	{
		pthread_mutex_unlock(&data->eat_mutex);
		if (all_check_frag(moniter, data))
		{
			pthread_mutex_lock(&moniter->flag_mutex);
			moniter->stop_flag = 1;
			pthread_mutex_unlock(&moniter->flag_mutex);
			return (1);
		}
		else
			pthread_mutex_unlock(&moniter->flag_mutex);
	}
	pthread_mutex_unlock(&data->eat_mutex);
	return (0);
}

void	*moniter_func(void *arg)
{
	t_moniter	*moniter;
	t_data		**data;


	moniter = (t_moniter *)arg;
	while (1)
	{
		data = moniter->data;
		if (moni_time_check(moniter, *data))
			break ;
		if (moni_eat_count_check(moniter, *data))
			break ;
		usleep(20);
		data++;
	}
	pthread_exit(NULL);
}
