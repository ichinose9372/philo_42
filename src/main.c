/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:51:07 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/03 14:44:57 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
