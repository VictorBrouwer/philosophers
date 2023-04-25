/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:45:11 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/25 15:37:31 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	check_args(char **argv, int argc)
{
	int	count;
	int	ttd;
	int	tte;
	int	tts;

	count = ft_atoi_prot(argv[1]);
	ttd = ft_atoi_prot(argv[2]);
	tte = ft_atoi_prot(argv[3]);
	tts = ft_atoi_prot(argv[4]);
	if (count < 1 || ttd < 1 || tte < 1 || tts < 1)
		return (EXIT_FAILURE);
	if (argc == 6 && (ft_atoi_prot(argv[5]) < 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}