/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:51:07 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/06 10:45:42 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_data *data, t_moniter *moniter, int status)
{
	pthread_mutex_lock(&moniter->flag_mutex);
	if (!moniter->stop_flag)
	{
		pthread_mutex_unlock(&moniter->flag_mutex);
		if (status == 0)
			printf("%ld %d is thinking\n", get_now_time(), data->num_philo);
		else if (status == 1)
			printf("%ld %d has taken a fork\n", get_now_time(), data->num_philo);
		else if (status == 2)
			printf("%ld %d is eating\n", get_now_time(), data->num_philo);
		else if (status == 3)
			printf("%ld %d is sleeping\n", get_now_time(), data->num_philo);
	}
	else
		pthread_mutex_unlock(&moniter->flag_mutex);
}

int	main(int argc, char	**argv)
{
	t_data			**data;
	t_moniter		*moniter;

	data = malloc_data(argc, argv);
	if (!data)
		return (0);
	moniter = make_moniter_init(data, argv);
	if (!moniter)
	{
		free_data(data);
		return (0);
	}
	if (init_data(argv, data, moniter))
	{
		free_all(data, moniter);
		return (0);
	}
	philo(data, moniter, philo_atoi(argv[1]));
	mutex_del(data, moniter, philo_atoi(argv[1]));
	free_all(data, moniter);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q philo");
// }
