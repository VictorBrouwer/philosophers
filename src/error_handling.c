/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:45:11 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/18 10:21:02 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(const char *str, int errno)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (errno != 1)
		exit(errno);
	exit(EXIT_FAILURE);
}

void	ft_putstr_fd(const char *s, int fd)
{
	int	x;

	x = 0;
	while (s[x])
	{
		write(fd, &s[x], 1);
		x++;
	}
}

int	ft_atoi_prot(const char *str)
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
			exit(EXIT_FAILURE);
		x++;
	}
	return (result * sign);
}
