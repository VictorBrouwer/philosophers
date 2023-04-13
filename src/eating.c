/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:14:53 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/13 13:53:34 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_eating(t_philo *philo)
{
	struct timeval tv;

	check_for_death(philo);
	lock_forks(philo);
	printf("%d %d is eating\n", (tv.tv_usec / 1000), philo->id);
	usleep(1000 * philo->time_to_eat);
	philo->meals_done++;
	if (gettimeofday(&tv, NULL) == -1)
		exit(EXIT_FAILURE);
	// printf("philo number %d finished eating at %ld %d \n", philo->id, tv.tv_sec, (tv.tv_usec / 1000));
	philo->time_last_meal = (tv.tv_usec / 1000);
	unlock_forks(philo);
}

void	lock_forks(t_philo *philo)
{
	struct timeval tv;

	if (pthread_mutex_lock(philo->fork_1) != 0)
		exit(EXIT_FAILURE);
	if (pthread_mutex_lock(philo->fork_2) != 0)
		exit(EXIT_FAILURE);
	if (gettimeofday(&tv, NULL) == -1)
		exit(EXIT_FAILURE);
	printf("%d %d has taken a fork\n", (tv.tv_usec / 1000), philo->id);
}

void	unlock_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->fork_1) != 0)
		exit(EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->fork_2) != 0)
		exit(EXIT_FAILURE);
}
