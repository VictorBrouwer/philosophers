/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:54:47 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/18 14:10:35 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_sleeping(t_philo *philo)
{
	unsigned long	start_sleep;

	start_sleep = get_time(philo);
	printf("%lu %d is sleeping\n", start_sleep, philo->id);
	while (get_time(philo) < (start_sleep + philo->info->time_to_sleep))
	{
		if (check_for_death(philo) == 1)
			break ;
		usleep(25);	
	}
}

