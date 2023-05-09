/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:45:11 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/09 14:40:44 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	atoi_check(const char *str)
{
	int	x;
	int	sign;
	int	result;

	x = 0;
	sign = 1;
	result = 0;
	while (str[x] == 32 || (str[x] >= 9 && str[x] <= 13))
		x++;
	if (str[x] == '-')
	{
		sign = -1;
		x++;
	}
	else if (str[x] == '+')
		x++;
	while (str[x] && str[x] >= '0' && str[x] <= '9')
	{
		result = result * 10;
		result = result + (str[x] - '0');
		if (result < 0 && (result != INT_MIN || sign == 1))
			return (ERROR);
		x++;
	}
	return (SUCCESS);
}

int	ft_atoi(const char *str)
{
	int	x;
	int	sign;
	int	result;

	x = 0;
	sign = 1;
	result = 0;
	while (str[x] == 32 || (str[x] >= 9 && str[x] <= 13))
		x++;
	if (str[x] == '-')
	{
		sign = -1;
		x++;
	}
	else if (str[x] == '+')
		x++;
	while (str[x] && str[x] >= '0' && str[x] <= '9')
	{
		result = result * 10;
		result = result + (str[x] - '0');
		x++;
	}
	return (result * sign);
}

int	check_args(char **argv, int argc)
{
	int	count;
	int	ttd;
	int	tte;
	int	tts;

	if (check_digits(argv[1]) == 1 || \
		check_digits(argv[2]) == 1 || \
		check_digits(argv[3]) == 1 || \
		check_digits(argv[4]) == 1)
		return (ERROR);
	if (atoi_check(argv[1]) == 1 || \
		atoi_check(argv[2]) == 1 || \
		atoi_check(argv[3]) == 1 || \
		atoi_check(argv[4]) == 1)
		return (ERROR);
	count = ft_atoi(argv[1]);
	ttd = ft_atoi(argv[2]);
	tte = ft_atoi(argv[3]);
	tts = ft_atoi(argv[4]);
	if (count < 1 || ttd < 1 || tte < 1 || tts < 1)
		return (ERROR);
	if (argc == 6 && (check_digits(argv[5]) == 1 || \
	(ft_atoi(argv[5]) < 1) || atoi_check(argv[5]) == 1))
		return (ERROR);
	return (SUCCESS);
}

int	check_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
