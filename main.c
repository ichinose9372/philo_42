/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:51:07 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/27 19:05:52 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define ARGC 5

int	g_full;

// void	check_args(int	argc, char **argv)
// {
// 	int	num;

// 	if (argc < 5)
// 		return (0);
// 	num = p_atoi(argv[1]);
// }

long	cal_time(struct timeval time, struct timeval now)
{
	long	now_time;
	long	start_time;

	now_time = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
	start_time = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;
	return ((time.tv_sec * 1000) + (now_time - start_time));
}

void	*philo_func(void *arg)
{
	t_data			*data;
	struct timeval	now;
	long			second;

	data = (t_data *)arg;
	gettimeofday(&now, NULL);
	printf(" %ld  %d  is thinking\n", cal_time(data->time, now), data->num);
	while (1)
	{
		if (g_full >= 100)
			break ;
		if (data->num % 2 == 0)
		{
			pthread_mutex_lock(data->right_fork);
			pthread_mutex_lock(data->left_fork);
			gettimeofday(&now, NULL);
			printf(" %ld %d has taken a fork\n", cal_time(data->time, now), data->num);
			printf(" %ld %d is eating\n", cal_time(data->time, now), data->num);
			pthread_mutex_unlock(data->left_fork);
			pthread_mutex_unlock(data->right_fork);
			usleep(200);
			g_full++;
			gettimeofday(&now, NULL);
			printf(" %ld %d thinking\n", cal_time(data->time, now), data->num);
		}
		else
		{
			pthread_mutex_lock(data->left_fork);
			pthread_mutex_lock(data->right_fork);
			gettimeofday(&now, NULL);
			printf(" %ld %d has taken a fork\n", cal_time(data->time, now), data->num);
			printf(" %ld %d eating\n", cal_time(data->time, now), data->num);
			pthread_mutex_unlock(data->right_fork);
			pthread_mutex_unlock(data->left_fork);
			usleep(200);
			g_full++;
			gettimeofday(&now, NULL);
			printf(" %ld %d thinking\n", cal_time(data->time, now), data->num);
		}
	}
	pthread_exit(NULL);
}

int	main(int argc, char	**argv)
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
		gettimeofday(&data[i].time, NULL);
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

