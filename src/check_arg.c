/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:26:08 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/05/02 17:07:31 by yichinos         ###   ########.fr       */
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

t_data	**check_args_and_malloc(int argc, char **argv, t_data **data)
{
	int	i;
	int	j;

	if (argc < 5)
		return (NULL);
	i = 1;
	while (argv[i])
	{
		if (ft_digit(argv[i++]))
			return (NULL);
	}
	i = 0;
	i = philo_atoi(argv[1]);
	if (i == -1)
		return (NULL);
	data = malloc(sizeof(t_data *) * (i + 1));
	if (!data)
		return (NULL);
	j = 0;
	while (j < i)
		data[++] = malloc(sizeof(t_data));
	data[j] = NULL;
	return (data);
}
