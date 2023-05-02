/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:18:08 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/05/02 16:45:55 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	cal_time(struct timeval time, struct timeval now)
{
	long	now_time;
	long	st_time;

	now_time = (now.tv_sec) * 1000 + (now.tv_usec) / 1000;
	st_time = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;
	return ((time.tv_sec * 1000) + (now_time - st_time));
}

long	get_now_time(void)
{
	long			now;
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	now = ((tmp.tv_sec) * 1000) + ((tmp.tv_usec) / 1000);
	return (now);
}

void	ft_usleep(long check_time, long time_to)
{
	long int	time;

	while (1)
	{
		time = get_now_time();
		if (time - check_time >= time_to)
			return ;
	}
}
