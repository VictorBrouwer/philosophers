/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:22:15 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/25 14:38:01 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	check_for_eol(t_philo *philo)
{
	bool is_philo_dead;

	pthread_mutex_lock(&philo->info->death_mutex);
	is_philo_dead = philo->info->is_dead;
	pthread_mutex_unlock(&philo->info->death_mutex);
	if (is_philo_dead)
		return (EXIT_FAILURE);
	if (philo->info->meals_to_finish != -1)
	{
		if (check_full_philos(philo) == 1)
			return (EXIT_FAILURE);
	}
	if (check_for_starvation(philo) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	die(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_mutex);
	philo->info->is_dead = true;
	pthread_mutex_unlock(&philo->info->death_mutex);
}

int	check_for_starvation(t_philo *philo)
{
	int	time_since_last_meal;

	pthread_mutex_lock(&philo->meals_mutex); // unsure if this mutex is needed
	time_since_last_meal = get_time(philo) - philo->time_last_meal;
	pthread_mutex_unlock(&philo->meals_mutex);
	if (time_since_last_meal > philo->info->time_to_die)
	{
		die(philo);
		printf("%lu %d died\n", get_time(philo), philo->id);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_full_philos(t_philo *philo)
{
	int	full_philos; // assign a stack variable to full philos to make mutex lock shorter

	pthread_mutex_lock(&philo->info->full_philo_mutex);
	full_philos = philo->info->full_philo_count;
	pthread_mutex_unlock(&philo->info->full_philo_mutex);
	if (full_philos == philo->info->philo_count) // check if all philos have eaten max amount of meals
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
