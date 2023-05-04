/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:04:53 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/04 17:48:00 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo(t_data **data, t_moniter *moniter, int num)
{
	int	i;

	i = 0;
	if (num == 1)
	{
		only_one(*data);
		return(0);
	}
	if (pthread_create(&(moniter->pid), NULL, moniter_func, moniter) != 0)
		return (1);
	while (i < num)
	{
		if (pthread_create((&(data[i])->pid), NULL, philo_func, data[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < num)
		pthread_join(data[i++]->pid, NULL);
	pthread_join(moniter->pid, NULL);
	return (0);
}

void	mutex_del(t_data **data, t_moniter *moniter, int num)
{
	int	i;

	i = 0;
	if (num == 1)
		return ;
	while (i < num)
	{
		pthread_mutex_destroy(&(data[i]->fork));
		pthread_mutex_destroy(&(data[i]->eat_mutex));
		pthread_mutex_destroy(&(data[i]->start_mutex));
		pthread_mutex_destroy(&(data[i]->last_mutex));
		i++;
	}
	pthread_mutex_destroy(&(moniter)->flag_mutex);
}
