/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:51:07 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/28 22:09:11 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define ARGC 5

int	g_full;

t_data	**check_args_and_malloc(int argc, char **argv, t_data **data)
{
	int	i;
	int j;

	if (argc < 5)
		return (NULL);
	i = 1;
	while (argv[i])
	{
		if (ft_digit(argv[i]))
			return (NULL);
		i++;
	}
	i = 0;
	i = atoi(argv[1]);
	if (i == -1)
		return (NULL);
	data = malloc(sizeof(t_data *) * i);
	if (!data)
		return (NULL);
	j = 0;
	while (j < i)
	{
		data[j] = malloc(sizeof(t_data));
		j++;
	}
	j = 0;
	while (data[j])
	{
		gettimeofday(&data[j]->time, NULL);
		data[j]->num_philo = j;
		data[j]->t_die = atoi(argv[2]);
		data[j]->t_eat = atoi(argv[3]);
		data[j]->must_eat = atoi(argv[4]);
		if (argc == 6)
			data[j]->must_eat = atoi(argv[5]);
		if (((data[j])->t_die == -1) || ((data[j])->t_eat == -1)
			|| ((data[j])->must_eat == -1))
			return (NULL);
		j++;
	}
	j = 0;
	while (data[j])
	{
		pthread_mutex_init(&(data[j])->fork, NULL);
		j++;
	}
	j = 0;
	while (data[j])
	{
		if (j != i - 1)
		{
			data[j]->left_fork = &(data[j])->fork;
			data[j]->right_fork = &(data[j + 1])->fork;
		}
		else
		{
			data[j]->left_fork = &(data[j])->fork;
			data[j]->right_fork = &(data[0])->fork;
		}
		j++;
	}
	return (data);
}

long	cal_time(struct timeval time, struct timeval now)
{
	long	now_time;
	long	st_time;

	now_time = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
	st_time = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;
	return ((time.tv_sec * 1000) + (now_time - st_time));
}

void	*philo_func(void *arg)
{
	t_data			*data;
	struct timeval	now;
	long			second;

	data = (t_data *)arg;
	gettimeofday(&now, NULL);
	printf(" %ld %d is thinking\n", cal_time(data->time, now), data->num_philo);
	while (1)
	{
		if (data->must_eat == 0)
			break ;
		if (data->num_philo % 2 == 0)
		{
			pthread_mutex_lock(data->right_fork);
			pthread_mutex_lock(data->left_fork);
			gettimeofday(&now, NULL);
			printf(" %ld %d has taken a fork\n", cal_time(data->time, now), data->num_philo);
			printf(" %ld %d is eating\n", cal_time(data->time, now), data->num_philo);
			pthread_mutex_unlock(data->left_fork);
			pthread_mutex_unlock(data->right_fork);
			gettimeofday(&(data)->last_eat, NULL);
			usleep(200);
			data->must_eat--;
			gettimeofday(&now, NULL);
			printf(" %ld %d thinking\n", cal_time(data->time, now), data->num_philo);
		}
		else
		{
			pthread_mutex_lock(data->left_fork);
			pthread_mutex_lock(data->right_fork);
			gettimeofday(&now, NULL);
			printf(" %ld %d has taken a fork\n", cal_time(data->time, now), data->num_philo);
			printf(" %ld %d eating\n", cal_time(data->time, now), data->num_philo);
			pthread_mutex_unlock(data->right_fork);
			pthread_mutex_unlock(data->left_fork);
			gettimeofday(&(data)->last_eat, NULL);
			usleep(200);
			data->must_eat--;
			gettimeofday(&now, NULL);
			printf(" %ld %d thinking\n", cal_time(data->time, now), data->num_philo);
		}
	}
	pthread_exit(NULL);
}

int	main(int argc, char	**argv)
{
	t_data			**data;
	t_data			**tmp;
	int				i;

	data = check_args_and_malloc(argc, argv, data);
	if (data == NULL)
		return (0);
	tmp = data;
	while (*tmp)
	{
		pthread_create((&(*tmp)->pid), NULL, philo_func, *tmp);
		tmp++;
	}
	tmp = data;
	while (*tmp)
	{
		pthread_join((*tmp)->pid, NULL);
		tmp++;
	}
	tmp = data;
	while (*tmp)
	{
		pthread_mutex_destroy(&(*tmp)->fork);
		tmp++;
	}
	return (0);
}

