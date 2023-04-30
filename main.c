/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:51:07 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/30 18:50:12 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	**check_args_and_malloc(int argc, char **argv, t_data **data)
{
	int	i;
	int	j;

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
	return (data);
}

void	init_data(char **argv, t_data **data, t_moniter *monu)
{
	int	i;
	int	num;

	num = atoi(argv[1]);
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&(data[i]->fork), NULL);
		i++;
	}
	i = 0;
	while (i < num)
	{
		data[i]->flag = 0;
		data[i]->count = 0;
		data[i]->num_philo = i;
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

void	set_moniter(t_moniter	*moniter, t_data	**main, char	**argv)
{

	moniter->data = main;
	moniter->t_eat = atoi(argv[2]);
	moniter->t_sleep = atoi(argv[3]);
	moniter->t_die = atoi(argv[4]);
	if (argv[5])
		moniter->must_eat = atoi(argv[5]);
	gettimeofday(&(moniter->moniter_time), NULL);
	pthread_mutex_init(&(moniter->mutex), NULL);
}

long	cal_time(struct timeval time, struct timeval now)
{
	long	now_time;
	long	st_time;

	now_time = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
	st_time = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;
	return ((time.tv_sec * 1000) + (now_time - st_time));
}

void	*moniter_func(void *arg)
{
	t_moniter	*moniter;
	t_data		**tmp;

	moniter = (t_moniter *)arg;
	while (1)
	{
		tmp = moniter->data;
		while (moniter->data)
		{
			// if (moniter->must_eat < (*(moniter->data))->count)
			// {
			// 	printf("NNNNNGGGG\n");
			// 	(*moniter->data)->flag = 1;
			// 	break ;
			// }
			// else
			// 	printf("OOOKKKKK\n");
			printf("moniter \n");
			moniter->data++;
			usleep(1000);
		}
		moniter->data = tmp;
	}
}

void	*philo_func(void *arg)
{
	t_data			*data;
	t_moniter		*moni;

	data = (t_data *)arg;
	printf("%d is thinking\n", data->num_philo);
	while (1)
	{
		if (data->num_philo % 2 == 0)
		{
			pthread_mutex_lock(&(data->moniter->mutex));
			pthread_mutex_unlock(&(data->moniter->mutex));
			if (data->flag == 1)
				break ;
			pthread_mutex_lock(data->left_fork);
			pthread_mutex_lock(data->right_fork);
			printf("%d has taken a fork\n", data->num_philo);
			printf("%d is eating\n", data->num_philo);
			data->count++;
			usleep(400);
			pthread_mutex_unlock(data->right_fork);
			pthread_mutex_unlock(data->left_fork);
			printf("%d thinking\n", data->num_philo);
		}
		else
		{
			pthread_mutex_lock(&(data->moniter->mutex));
			//監視スレッドチェック処理。
			pthread_mutex_unlock(&(data->moniter->mutex));
			pthread_mutex_lock(data->right_fork);
			pthread_mutex_lock(data->left_fork);
			printf("%d has taken a fork\n", data->num_philo);
			printf("%d eating\n", data->num_philo);
			data->count++;
			pthread_mutex_unlock(data->left_fork);
			pthread_mutex_unlock(data->right_fork);
			printf("%d thinking\n", data->num_philo);
		}
	}
	pthread_exit(NULL);
}

int	main(int argc, char	**argv)
{
	t_data			**data;
	t_moniter		*moniter;
	int				i;

	i = 0;
	data = check_args_and_malloc(argc, argv, data);
	if (data == NULL)
		return (0);
	moniter = malloc(sizeof(t_moniter));
	if (moniter == NULL)
	{
		free(data);
		return (0);
	}
	init_data(argv, data, moniter);
	set_moniter(moniter, data, argv);
	pthread_create(&(moniter->pid), NULL, moniter_func, moniter);
	while (i < atoi(argv[1]))
	{
		pthread_create((&(data[i])->pid), NULL, philo_func, data[i]);
		i++;
	}
	i = 0;
	while (i < atoi(argv[1]))
		pthread_join(data[i++]->pid, NULL);
	i = 0;
	while (i < atoi(argv[1]))
		pthread_mutex_destroy(&(data[i++]->fork));
	free(data);
	return (0);
}
