/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:22:15 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/12 09:17:18 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_eol(t_philo *philo)
{
	if (philo->info->is_dead)
		return (ERROR);
	if (philo->info->meals_to_finish != -1)
	{
		if (check_full_philos(philo) == 1)
			return (ERROR);
	}
	if (check_for_starvation(philo) == 1)
		return (ERROR);
	return (SUCCESS);
}

int	check_for_starvation(t_philo *philo)
{
	int	time_since_last_meal;

	pthread_mutex_lock(&philo->meals_mutex);
	time_since_last_meal = get_time(philo) - philo->time_last_meal;
	if (time_since_last_meal > philo->info->time_to_die)
	{
		philo->info->is_dead = true;
		printf("%lu %d died\n", get_time(philo), philo->id);
		pthread_mutex_unlock(&philo->meals_mutex);
		return (ERROR);
	}
	pthread_mutex_unlock(&philo->meals_mutex);
	return (SUCCESS);
}

int	check_full_philos(t_philo *philo)
{
	int	full_philos;

	pthread_mutex_lock(&philo->info->full_philo_mutex);
	full_philos = philo->info->full_philo_count;
	if (full_philos == philo->info->philo_count)
	{
		pthread_mutex_unlock(&philo->info->full_philo_mutex);
		return (ERROR);
	}
	pthread_mutex_unlock(&philo->info->full_philo_mutex);
	return (SUCCESS);
}
