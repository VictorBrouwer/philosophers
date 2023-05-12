/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:54:47 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/11 16:46:08 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_sleeping(t_philo *philo, int time)
{
	unsigned long	start_sleep;

	start_sleep = get_time(philo);
	while (get_time(philo) < (start_sleep + time))
	{
		pthread_mutex_lock(&philo->info->check_for_eol_mutex);
		if (check_for_eol(philo) == 1)
		{
			pthread_mutex_unlock(&philo->info->check_for_eol_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->info->check_for_eol_mutex);
		usleep(250);
	}
	return (0);
}
