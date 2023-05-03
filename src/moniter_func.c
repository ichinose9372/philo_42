/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:22:02 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/03 23:03:08 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*flag_make(t_moniter *moniter)
{
	int	*flag;

	flag = malloc(sizeof(int) * (moniter->philo_count));
	if (flag == NULL)
		return (NULL);
	memset(flag, 0, moniter->philo_count);
	return (flag);
}

int	cheack_all_flag(int *flag, t_moniter *moniter)
{
	int	i;

	i = 0;
	while (i < moniter->philo_count)
	{
		if (flag[i] != 1)
			return (0);
		i++;
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
		printf("%ld %d died\n", get_now_time(), data->num_philo);
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

int	moni_eat_count_check(t_moniter *moniter, t_data *data, int *flag)
{

	pthread_mutex_lock(&data->eat_mutex);
	if (data->eat_count >= moniter->must_eat)
	{
		flag[data->num_philo] = 1;
		pthread_mutex_unlock(&data->eat_mutex);
		if (cheack_all_flag(flag, moniter))
		{
			pthread_mutex_lock(&moniter->flag_mutex);
			moniter->stop_flag = 1;
			pthread_mutex_unlock(&moniter->flag_mutex);
			return (1);
		}
		else
			return (0);
	}
	else
		pthread_mutex_unlock(&data->eat_mutex);
	return (0);
}

void	*moniter_func(void *arg)
{
	t_moniter	*moniter;
	t_data		**data;
	int			*flag;

	moniter = (t_moniter *)arg;
	flag = flag_make(moniter);
	if (flag == NULL)
		pthread_exit(NULL);
	while (1)
	{
		data = moniter->data;
		while (*data)
		{
			if (moni_time_check(moniter, *data))
				return (NULL);
			if (moni_eat_count_check(moniter, *data, flag))
				return (NULL);
			usleep(20);
			data++;
		}
	}
	pthread_exit(NULL);
}
