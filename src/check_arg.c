/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:26:08 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/05/03 11:40:51 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_atoi(char *str)
{
	int	len;

	len = 0;
	if (*str == '+')
		str++;
	while (*str)
	{
		len += *str - '0';
		len *= 10;
		str++;
		if (len >= INT_MAX)
		{
			len = INT_MAX;
			return (len);
		}
	}
	len /= 10;
	return (len);
}

int	ft_digit(char *str)
{
	int	i;

	i = 0;
	if (!(str[i] >= '0' && str[i] <= '9')
		&& !(str[i] == '+' && str[i + 1] != '\0'))
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

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5)
		return (-1);
	i = 1;
	while (argv[i])
	{
		if (ft_digit(argv[i++]))
			return (-1);
	}
	i = 0;
	i = philo_atoi(argv[1]);
	if (i == -1)
		return (-1);
	return (i);
}

t_data	**malloc_data(int argc, char **argv)
{
	int		i;
	t_data	**data;

	i = check_args(argc, argv);
	if (i == -1)
		return (NULL);
	data = malloc(sizeof(t_data *) * (i + 1));
	if (!data)
		return (NULL);
	i = 0;
	while (i < philo_atoi(argv[1]))
	{
		data[i] = malloc(sizeof(t_data));
		if (data[i] == NULL)
		{
			free_all(data);
			return (NULL);
		}
		i++;
	}
	data[i] = NULL;
	return (data);
}
