/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:54:37 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/04 21:19:00 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*only_one_func(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	printf("%ld %d has taken a fork\n", get_now_time(), data->num_philo);
	pthread_exit(NULL);
}

int	only_one(t_data *data)
{
	if (pthread_create(&(data->pid), NULL, only_one_func, data) != 0)
		return (1);
	pthread_join(&(*data->pid), NULL);
	pthread_mutex_destroy(&(data->fork));
	pthread_mutex_destroy(&(data->eat_mutex));
	pthread_mutex_destroy(&(data->start_mutex));
	pthread_mutex_destroy(&(data->last_mutex));
	return (0);
}
