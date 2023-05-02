/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:51:07 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/02 16:51:31 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*moniter_func(void *arg)
{
	t_moniter	*moniter;
	t_data		**data;
	int			count;

	moniter = (t_moniter *)arg;
	while (1)
	{
		count = 0;
		data = moniter->data;
		while (*data)
		{
			pthread_mutex_lock(&(*data)->start_mutex);
			pthread_mutex_lock(&(*data)->last_mutex);
			if ((moniter->t_die) < (*data)->start_eat - (*data)->last_eat)
			{
				pthread_mutex_unlock(&(*data)->start_mutex);
				pthread_mutex_unlock(&(*data)->last_mutex);
				pthread_mutex_lock(&(moniter)->flag_mutex);
				moniter->stop_flag = 1;
				printf("%ld %d died\n", get_now_time(), (*data)->num_philo);
				pthread_mutex_unlock(&(moniter)->flag_mutex);
				return (NULL);
			}
			else
			{
				pthread_mutex_unlock(&(*data)->start_mutex);
				pthread_mutex_unlock(&(*data)->last_mutex);
			}
			pthread_mutex_lock(&(*data)->eat_mutex);
			if ((*data)->eat_count >= moniter->must_eat)
			{
				pthread_mutex_unlock(&(*data)->eat_mutex);
				pthread_mutex_lock(&(moniter)->flag_mutex);
				count++;
				if (count == moniter->philo_count)
				{
					moniter->stop_flag = 1;
					pthread_mutex_unlock(&(moniter)->flag_mutex);
					return (NULL);
				}
				else
					pthread_mutex_unlock(&(moniter)->flag_mutex);
			}
			else
				pthread_mutex_unlock(&(*data)->eat_mutex);
			data++;
		}
	}
}

void	*philo_func(void *arg)
{
	t_data			*data;
	t_moniter		*moni;
	long			time;

	data = (t_data *)arg;
	moni = data->moniter;
	while (1)
	{
		time = 0;
		printf("%ld %d is thinking\n", get_now_time(), data->num_philo);
		if (data->num_philo % 2 == 0)
		{
			pthread_mutex_lock(&(moni)->flag_mutex);
			if (moni->stop_flag)
			{
				pthread_mutex_unlock(&(moni)->flag_mutex);
				break ;
			}
			else
				pthread_mutex_unlock(&(moni)->flag_mutex);
			pthread_mutex_lock(data->left_fork);
			pthread_mutex_lock(data->right_fork);
			printf("%ld %d has taken a fork\n", get_now_time(), data->num_philo);
			pthread_mutex_lock(&(data->start_mutex));
			data->start_eat = get_now_time();
			pthread_mutex_unlock(&(data->start_mutex));
			printf("%ld %d is eating\n", get_now_time(), data->num_philo);
			pthread_mutex_lock(&(data->eat_mutex));
			data->eat_count++;
			ft_usleep((data)->start_eat, moni->t_eat);
			pthread_mutex_unlock(&(data->eat_mutex));
			pthread_mutex_unlock(data->right_fork);
			pthread_mutex_unlock(data->left_fork);
			pthread_mutex_lock(&(data->last_mutex));
			data->last_eat = get_now_time();
			pthread_mutex_unlock(&(data->last_mutex));
			pthread_mutex_lock(&(moni)->flag_mutex);
			if (moni->stop_flag)
			{
				pthread_mutex_unlock(&(moni)->flag_mutex);
				break ;
			}
			else
				pthread_mutex_unlock(&(moni)->flag_mutex);
			printf("%ld %d  is sleeping\n", get_now_time(), data->num_philo);
			ft_usleep((data)->last_eat, moni->t_sleep);
		}
		else
		{
			printf("%ld %d is thinking\n", get_now_time(), data->num_philo);
			pthread_mutex_lock(&(moni)->flag_mutex);
			if (moni->stop_flag)
			{
				pthread_mutex_unlock(&(moni)->flag_mutex);
				break ;
			}
			else
				pthread_mutex_unlock(&(moni)->flag_mutex);
			pthread_mutex_lock(data->right_fork);
			pthread_mutex_lock(data->left_fork);
			printf("%ld %d has taken a fork\n", get_now_time(), data->num_philo);
			pthread_mutex_lock(&(data->start_mutex));
			data->start_eat = get_now_time();
			pthread_mutex_unlock(&(data->start_mutex));
			printf("%ld %d is eating\n", get_now_time(), data->num_philo);
			pthread_mutex_lock(&(data->eat_mutex));
			data->eat_count++;
			ft_usleep((data)->start_eat, moni->t_eat);
			pthread_mutex_unlock(&(data->eat_mutex));
			pthread_mutex_unlock(data->left_fork);
			pthread_mutex_unlock(data->right_fork);
			pthread_mutex_lock((&data->last_mutex));
			data->last_eat = get_now_time();
			pthread_mutex_unlock(&(data->last_mutex));
			pthread_mutex_lock(&(moni)->flag_mutex);
			if (moni->stop_flag)
			{
				pthread_mutex_unlock(&(moni)->flag_mutex);
				break ;
			}
			else
				pthread_mutex_unlock(&(moni)->flag_mutex);
			printf("%ld %d is sleeping\n", get_now_time(), data->num_philo);
			ft_usleep((data)->last_eat, moni->t_sleep);
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
	data = NULL;
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
	return (0);
	pthread_create(&(moniter->pid), NULL, moniter_func, moniter);
	while (i < atoi(argv[1]))
	{
		pthread_create((&(data[i])->pid), NULL, philo_func, data[i]);
		i++;
	}
	i = 0;
	while (i < atoi(argv[1]))
		pthread_join(data[i++]->pid, NULL);
	pthread_join(moniter->pid, NULL);
	i = 0;
	while (i < atoi(argv[1]))
		pthread_mutex_destroy(&(data[i++]->fork));
	pthread_mutex_destroy(&(moniter)->flag_mutex);
	i = 0;
	while (i < atoi(argv[1]))
		free(data[i++]);
	free(data);
	free(moniter);
	return (0);
}
