/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:14:58 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/25 16:03:40 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_eating(t_philo *philo)
{
	if (take_forks(philo) == 1)
		return (ERROR);
	if (print_action(philo, "is eating") == 1)
	{
		pthread_mutex_unlock(philo->fork_1);
		pthread_mutex_unlock(philo->fork_2);
		return (ERROR);
	}
	pthread_mutex_lock(&philo->meals_mutex);
	philo->time_last_meal = get_time(philo);
	pthread_mutex_unlock(&philo->meals_mutex);
	start_sleeping(philo, philo->info->time_to_eat);
	pthread_mutex_unlock(philo->fork_1);
	pthread_mutex_unlock(philo->fork_2);
	if (philo->info->meals_to_finish != -1)
		update_meals(philo);
	return (0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_1);
	if (print_action(philo, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(philo->fork_1);
		return (ERROR);
	}
	if (philo->fork_2 == NULL)
		return (ERROR);
	pthread_mutex_lock(philo->fork_2);
	if (print_action(philo, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(philo->fork_1);
		pthread_mutex_unlock(philo->fork_2);
		return (ERROR);
	}
	return (0);
}

void	update_meals(t_philo *philo)
{
	philo->meals_done++;
	if (philo->meals_done == philo->info->meals_to_finish)
	{
		pthread_mutex_lock(&philo->info->full_philo_mutex);
		philo->info->full_philo_count++;
		pthread_mutex_unlock(&philo->info->full_philo_mutex);
	}
}
