/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:26:08 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2023/04/28 20:57:38 by ichinoseyuu      ###   ########.fr       */
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

// int	p_atoi(char *str)
// {
// 	int	ret;

// 	ret = 0;
// 	if (*str == '-')
// 		return (-1);
// 	if (*str == '+')
// 		str++;
// 	while (*str)
// 	{
// 		printf("%c\n", *str);
// 		ret = *str + '0';
// 		ret *= 10;
// 		if (ret > 2147483647)
// 			return (-1);
// 		str++;
// 	}
// 	return (ret);
// }
