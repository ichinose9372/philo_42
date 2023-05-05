/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:26:08 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/05/05 14:20:53 by ichinoseyuu      ###   ########.fr       */
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

	if ((argc < 5) || (argc > 6))
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
