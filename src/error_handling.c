/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:45:11 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/13 13:10:53 by vbrouwer         ###   ########.fr       */
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
