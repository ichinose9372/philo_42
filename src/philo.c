/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:04:53 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/05 14:14:27 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo(t_data **data, t_moniter *moniter, int num)
{
	int	i;

	i = 0;
	if (num == 1)
	{
		only_one(*data);
		return ;
	}
	if (pthread_create(&(moniter->pid), NULL, moniter_func, moniter) != 0)
		return ;
	while (i < num)
	{
		if (pthread_create((&(data[i])->pid), NULL, philo_func, data[i]) != 0)
			return ;
		i++;
	}
	i = 0;
	while (i < num)
		pthread_join(data[i++]->pid, NULL);
	pthread_join(moniter->pid, NULL);
	return ;
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
