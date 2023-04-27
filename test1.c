/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:18:21 by yichinos          #+#    #+#             */
/*   Updated: 2023/04/27 11:19:19 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
	int		num;
}	t_data;

void	*thread_func(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	printf("my num = %d\n", data->num);
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t	pid[5];
	int			num;
	t_data		philo[5];

	num = 5;
	while (num > 0)
	{
		philo[num - 1].num = num;
		pthread_create(&pid[num - 1], NULL, thread_func, &philo[num -1]);
		num--;
	}
	num = 5;
	while (num > 0)
	{
		pthread_join(pid[num - 1], NULL);
		num--;
	}
	return (0);
}
