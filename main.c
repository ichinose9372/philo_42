/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:51:07 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/27 16:02:15 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define ARGC 5

int	g_full;

void	*philo_func(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (g_full >= ARGC)
			break ;
		if (data->num % 2 == 0)
		{
			pthread_mutex_lock(data->right_fork);
			pthread_mutex_lock(data->left_fork);
			printf("phillo [ %d ] eating\n", data->num);
			pthread_mutex_unlock(data->left_fork);
			pthread_mutex_unlock(data->right_fork);
			printf("phillo [ %d ] sleeping\n", data->num);
			usleep(200);
			g_full++;
		}
		else
		{
			pthread_mutex_lock(data->left_fork);
			pthread_mutex_lock(data->right_fork);
			printf("phillo [ %d ] eating\n", data->num);
			pthread_mutex_unlock(data->right_fork);
			pthread_mutex_unlock(data->left_fork);
			printf("phillo [ %d ] sleeping\n", data->num);
			usleep(200);
			g_full++;
		}
	}
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t		pid[ARGC];
	t_data			data[ARGC];
	int				i;

	i = 0;
	while (i < ARGC)
	{
		pthread_mutex_init(&data[i].fork, NULL);
		i++;
	}
	i = 0;
	while (i < ARGC)
	{
		if (i != ARGC -1)
		{
			data[i].left_fork = &data[i].fork;
			data[i].right_fork = &data[i + 1].fork;
		}
		else
		{
			data[i].left_fork = &data[i].fork;
			data[i].right_fork = &data[0].fork;
		}
		i++;
	}
	i = 0;
	while (i < ARGC)
	{
		data[i].num = i;
		pthread_create(&pid[i], NULL, philo_func, &data[i]);
		i++;
	}
	i = 0;
	while (i < ARGC)
	{
		pthread_join(pid[i], NULL);
		i++;
	}
	i = 0;
	while (i < ARGC)
	{
		pthread_mutex_destroy(&data[i].fork);
		i++;
	}
	return (0);
}

