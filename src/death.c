/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:22:15 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/21 11:31:49 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	check_for_eol(t_philo *philo)
{
	int		time_since_last_meal;

	pthread_mutex_lock(&philo->info->death_mutex);
	if (philo->info->is_dead)
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	if (philo->info->meals_to_finish != -1)
	{
		if (check_meals(philo))
			return (EXIT_FAILURE);
	}
	time_since_last_meal = get_time(philo) - philo->time_last_meal;
	// printf("time since last meal of %d is %d\n", philo->id, time_since_last_meal);
	if (time_since_last_meal > philo->info->time_to_die)
	{
		die(philo);
		printf("%lu %d died\n", get_time(philo), philo->id);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	die(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->death_mutex);
	philo->info->is_dead = 1;
	pthread_mutex_unlock(&philo->info->death_mutex);
}

