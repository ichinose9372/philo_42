/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:51:07 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/03 12:20:11 by yichinos         ###   ########.fr       */
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
				// printf("%ld %d died\n", get_now_time(), (*data)->num_philo);
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
				printf("%ld %d died\n", get_now_time(), (data)->num_philo);
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
				printf("%ld %d died\n", get_now_time(), (data)->num_philo);
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
	moniter = NULL;
	data = malloc_data(argc, argv);
	moniter = make_moniter_init(data, argv);
	if (moniter == NULL || data == NULL)
		return (0);
	init_data(argv, data, moniter);
	philo(data, moniter, philo_atoi(argv[1]));
	mutex_del(data, moniter, philo_atoi(argv[1]));
	free_all(data);
	free(moniter);
	return (0);
}
