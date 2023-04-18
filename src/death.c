/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:22:15 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/18 14:08:52 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	check_for_death(t_philo *philo)
{
	int		time_since_last_meal;

	time_since_last_meal = get_time(philo) - philo->time_last_meal;
	// printf("time since last meal of %d is %d\n", philo->id, time_since_last_meal);
	if (time_since_last_meal > philo->info->time_to_die && philo->time_last_meal != 0)
	{
		printf("%lu %d died\n", get_time(philo), philo->id);
		philo->info->is_dead = 1; // gebruik hier een mutex
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
