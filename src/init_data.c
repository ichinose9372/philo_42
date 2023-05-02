/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:16:28 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/05/02 16:54:52 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_data(char **argv, t_data **data, t_moniter *monu)
{
	int i;
	int num;

	num = atoi(argv[1]);
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&(data[i]->fork), NULL);
		pthread_mutex_init(&(data[i]->eat_mutex), NULL);
		pthread_mutex_init(&(data[i]->last_mutex), NULL);
		pthread_mutex_init(&(data[i]->start_mutex), NULL);
		i++;
	}
	i = 0;
	while (i < num)
	{
		data[i]->num_philo = i;
		data[i]->eat_count = 0;
		data[i]->start_eat = get_now_time();
		data[i]->last_eat = get_now_time();
		data[i]->moniter = monu;
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

void set_moniter(t_moniter *moniter, t_data **main, char **argv)
{
	printf("%d\t%d\t%d\t%d\n", philo_atoi(argv[1]), philo_atoi(argv[2]), philo_atoi(argv[3]), philo_atoi(argv[4]));
	moniter->data = main;
	moniter->philo_count = atoi(argv[1]);
	moniter->t_die = atoi(argv[2]);
	moniter->t_eat = atoi(argv[3]);
	moniter->t_sleep = atoi(argv[4]);
	if (argv[5])
		moniter->must_eat = atoi(argv[5]);
	moniter->stop_flag = 0;
	pthread_mutex_init(&(moniter)->flag_mutex, NULL);
}
