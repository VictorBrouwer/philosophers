/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:14:53 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/12 17:21:20 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_eating(t_philo *philo)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit(EXIT_FAILURE);
	if ((tv.tv_usec - philo->time_last_meal) >= philo->time_to_die && philo->time_last_meal != 0)
		die(philo);
	printf("%d %d is eating\n", tv.tv_usec, philo->id);
	usleep(philo->time_to_eat);
	philo->meals_done++;
	if (gettimeofday(&tv, NULL) == -1)
		exit(EXIT_FAILURE);
	// printf("philo number %d finished eating at %ld %d \n", philo->id, tv.tv_sec, tv.tv_usec);
	philo->time_last_meal = tv.tv_usec;
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
	printf("%d %d has taken a fork\n", tv.tv_usec, philo->id);
}

void	unlock_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->fork_1) != 0)
		exit(EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->fork_2) != 0)
		exit(EXIT_FAILURE);
}
