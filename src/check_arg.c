/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:26:08 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/05/06 10:28:17 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	philo_atoi(char *str)
{
	long	number;

	number = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (-1);
		str++;
		if (!(*str >= '0' && *str <= '9'))
			return (-1);
	}
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += *str - '0';
		str++;
	}
	if (number > INT_MAX)
		return (-1);
	return (number);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if ((argc < 5) || (argc > 6))
		return (-1);
	i = philo_atoi(argv[1]);
	if (i == -1)
		return (-1);
	return (i);
}
