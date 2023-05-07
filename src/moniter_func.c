/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:22:02 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/07 11:24:43 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	moni_time_check(t_moniter *moniter, t_data *data)
{
	pthread_mutex_lock(&data->start_mutex);
	if (moniter->t_die <= get_now_time() - data->start_eat)
	{
		pthread_mutex_unlock(&data->start_mutex);
		pthread_mutex_lock(&moniter->flag_mutex);
		moniter->stop_flag = 1;
		pthread_mutex_unlock(&moniter->flag_mutex);
		printf("%ld %d died\n", get_now_time(), data->num_philo);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->start_mutex);
	return (0);
}

int	moni_eat_count_check(t_moniter *moniter, t_data *data, int *num)
{
	pthread_mutex_lock(&data->eat_mutex);
	if (moniter->must_eat > 0 && data->eat_count >= moniter->must_eat)
	{
		*num += 1;
		if (*num == moniter->philo_count)
		{
			pthread_mutex_unlock(&data->eat_mutex);
			pthread_mutex_lock(&moniter->flag_mutex);
			moniter->stop_flag = 1;
			pthread_mutex_unlock(&moniter->flag_mutex);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&data->eat_mutex);
			return (0);
		}
	}
	else
		pthread_mutex_unlock(&data->eat_mutex);
	return (0);
}

void	*moniter_func(void *arg)
{
	t_moniter	*moniter;
	t_data		**data;
	int			num;

	moniter = (t_moniter *)arg;
	while (1)
	{
		num = 0;
		data = moniter->data;
		while (*data)
		{
			if (moni_time_check(moniter, *data))
				pthread_exit(NULL);
			if (moni_eat_count_check(moniter, *data, &num))
				pthread_exit(NULL);
			usleep(30);
			data++;
		}
	}
}
