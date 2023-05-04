/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:16:28 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/05/04 17:12:47 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_mutex_set(t_data **data, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(&(data[i]->fork), NULL) != 0)
			return (1);
		if (pthread_mutex_init(&(data[i]->eat_mutex), NULL) != 0)
			return (1);
		if (pthread_mutex_init(&(data[i]->last_mutex), NULL) != 0)
			return (1);
		if (pthread_mutex_init(&(data[i]->start_mutex), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	data_other_set(t_data **data, int num, t_moniter *mon)
{
	int	i;

	i = 0;
	while (i < num)
	{
		data[i]->num_philo = i;
		data[i]->eat_count = 0;
		data[i]->start_eat = get_now_time();
		data[i]->last_eat = get_now_time();
		data[i]->moniter = mon;
		if (i == num - 1)
		{
			data[i]->left_fork = &(data[i]->fork);
			data[i]->right_fork = &(data[(i + 1) % num]->fork);
		}
		else
		{
			data[i]->left_fork = &(data[i]->fork);
			data[i]->right_fork = &(data[i + 1]->fork);
		}
		i++;
	}
}

int	init_data(char **argv, t_data **data, t_moniter *mon)
{
	int	num;

	num = philo_atoi(argv[1]);
	if (data_mutex_set(data, num))
		return (1);
	data_other_set(data, num, mon);
	return (0);
}

t_moniter	*make_moniter_init(t_data **main, char **argv)
{
	t_moniter	*moniter;

	moniter = malloc(sizeof(t_moniter));
	if (moniter == NULL)
		return (NULL);
	moniter->data = main;
	moniter->philo_count = philo_atoi(argv[1]);
	moniter->t_die = philo_atoi(argv[2]);
	moniter->t_eat = philo_atoi(argv[3]);
	moniter->t_sleep = philo_atoi(argv[4]);
	if (argv[5])
		moniter->must_eat = philo_atoi(argv[5]);
	moniter->stop_flag = 0;
	if (pthread_mutex_init(&(moniter)->flag_mutex, NULL) != 0)
		return (NULL);
	return (moniter);
}
