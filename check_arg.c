/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:26:08 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/05/01 15:28:40 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_digit(char *str)
{
	int	i;

	i = 0;
	if (!(str[i] >= '0' && str[i] <= '9') && !(str[i] == '+'))
		return (1);
	i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

t_data **check_args_and_malloc(int argc, char **argv, t_data **data)
{
	int i;
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
	data = malloc(sizeof(t_data *) * (i + 1));
	if (!data)
		return (NULL);
	j = 0;
	while (j < i)
	{
		data[j] = malloc(sizeof(t_data));
		j++;
	}
	data[j] = NULL;
	return (data);
}
