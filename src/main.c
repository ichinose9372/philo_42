/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:51:07 by yichinos          #+#    #+#             */
/*   Updated: 2023/05/03 23:02:55 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char	**argv)
{
	t_data			**data;
	t_moniter		*moniter;

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
