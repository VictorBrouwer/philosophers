/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:54:47 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/25 16:08:28 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_sleeping(t_philo *philo, int time)
{
	unsigned long	start_sleep;

	start_sleep = get_time(philo);
	while (get_time(philo) < (start_sleep + time))
	{
		if (check_for_eol(philo) == 1)
			return (1);
		usleep(250);
	}
	return (0);
}
