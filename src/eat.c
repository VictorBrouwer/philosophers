/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:14:58 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/21 11:30:51 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	start_eating(t_philo *philo)
// {
// 	lock_forks(philo);
// 	pthread_mutex_lock(&philo->info->print_mutex);
// 	if (print_action(philo, "is eating") == 1)
// 	{
// 		pthread_mutex_unlock(&philo->info->print_mutex);
// 		return (1);	
// 	}
// 	pthread_mutex_unlock(&philo->info->print_mutex);
// 	usleep(1000 * philo->info->time_to_eat);
// 	philo->meals_done++;
// 	philo->time_last_meal = get_time(philo);
// 	unlock_forks(philo);
// 	return (0);
// }

int	check_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_mutex);
	if (philo->meals_done >= philo->info->meals_to_finish)
	{
		die(philo);
		pthread_mutex_unlock(&philo->meals_mutex);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->meals_mutex);
	return (EXIT_SUCCESS);
}