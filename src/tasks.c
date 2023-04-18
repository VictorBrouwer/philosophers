/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:14:53 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/17 14:19:52 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_eating(t_philo *philo)
{
	check_for_death(philo);
	lock_forks(philo);
	printf("%lu %d is eating\n", get_time(philo) , philo->id);
	usleep(1000 * philo->info->time_to_eat);
	philo->meals_done++;
	philo->time_last_meal = get_time(philo);
	unlock_forks(philo);
}

void	lock_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->fork_1) != 0)
		exit(EXIT_FAILURE);
	if (pthread_mutex_lock(philo->fork_2) != 0)
		exit(EXIT_FAILURE);
	printf("%lu %d has taken a fork\n", get_time(philo) , philo->id);
}

void	unlock_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->fork_1) != 0)
		exit(EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->fork_2) != 0)
		exit(EXIT_FAILURE);
}

void	start_sleeping(t_philo *philo)
{
	printf("%lu %d is sleeping\n", get_time(philo), philo->id);
	usleep(1000 * philo->info->time_to_sleep);
}

void	start_thinking(t_philo *philo)
{
	check_for_death(philo);
	printf("%lu %d is thinking\n", get_time(philo), philo->id);
}
