/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:22:15 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/13 13:40:50 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	check_for_death(t_philo *philo)
{
	struct	timeval tv;
	int		time_since_last_meal;

	if (gettimeofday(&tv, NULL) == -1)
		exit(EXIT_FAILURE);
	if (philo->time_last_meal > (tv.tv_usec / 1000))
		tv.tv_usec += 1000000;
	time_since_last_meal = (tv.tv_usec / 1000) - philo->time_last_meal;
	printf("time since last meal of %d is %d\n", philo->id, time_since_last_meal);
	if (time_since_last_meal >= philo->time_to_die && philo->time_last_meal != 0)
		die(philo);
}

void	die(t_philo *philo)
{
	struct	timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit(EXIT_FAILURE);
	printf("%d %d died\n", (tv.tv_usec / 1000), philo->id);
	philo->is_dead = 1;
	exit(EXIT_FAILURE);
}