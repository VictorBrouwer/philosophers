/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:14:53 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/21 11:23:40 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->info->start_mutex);
	pthread_mutex_unlock(&philo->info->start_mutex);
	while(1)
	{
		pthread_mutex_lock(philo->fork_1); // lock fork mutexes
		pthread_mutex_lock(philo->fork_2);
		pthread_mutex_lock(&philo->print_mutex); // lock print mutex
		if (print_action(philo, "has taken a fork") == 1)
		{
			pthread_mutex_unlock(philo->fork_1); // if dead unlock forks, unlock print mutex and return
			pthread_mutex_unlock(philo->fork_2);
			pthread_mutex_unlock(&philo->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->print_mutex); //if not dead unlock print mutex and start eating
		pthread_mutex_lock(&philo->print_mutex); // lock print mutex again
		if (print_action(philo, "is eating") == 1)
		{
			pthread_mutex_unlock(philo->fork_1); // if dead unlock forks, unlock print mutex and return
			pthread_mutex_unlock(philo->fork_2);
			pthread_mutex_unlock(&philo->print_mutex);
			break ;	
		}
		pthread_mutex_unlock(&philo->print_mutex); // if not dead, unlock print mutex
		usleep(1000 * philo->info->time_to_eat); //sleep for time to eat
		philo->meals_done++; // increase meals
		philo->time_last_meal = get_time(philo); // save time of meal
		pthread_mutex_unlock(philo->fork_1); // unlock forks
		pthread_mutex_unlock(philo->fork_2);
		pthread_mutex_lock(&philo->print_mutex); // lock print mutex
		if (print_action(philo, "is sleeping") == 1) // if dead unlock print mutex and return
		{
			pthread_mutex_unlock(&philo->print_mutex);
			break ;	
		}
		pthread_mutex_unlock(&philo->print_mutex); // if not dead, unlock print mutex
		start_sleeping(philo); // start sleeping
		pthread_mutex_lock(&philo->print_mutex); // lock print mutex
		if (print_action(philo, "is thinking") == 1) // if dead unlock print mutex and return
		{
			pthread_mutex_unlock(&philo->print_mutex);
			break ;	
		}
		pthread_mutex_unlock(&philo->print_mutex); // if not dead, unlock print mutex
		// if (start_eating(philo) == 1)
		// 	break ;
		// start_sleeping(philo);
		// if (start_thinking(philo) == 1)
		// 	break ;
		// if (philo->meals_done >= philo->info->meals_to_finish && philo->info->meals_to_finish != -1)
		// 	break ;
	}
	return ((void *)philo);
}

int	print_action(t_philo *philo, char *action)
{
	if (check_for_eol(philo) == 1)
	{
		return (EXIT_FAILURE);
	}
	printf("%lu %d %s\n", get_time(philo), philo->id, action);
	return (0);
}

// void	lock_forks(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->fork_1);
// 	pthread_mutex_lock(philo->fork_2);
// 	pthread_mutex_lock(&philo->info->print_mutex);
// 	if (print_action(philo, "has taken a fork") == 1)
// 	{
// 		unlock_forks(philo);
// 		pthread_mutex_unlock(&philo->info->print_mutex);
// 		return ;	
// 	}
// 	pthread_mutex_unlock(&philo->info->print_mutex);
// }

// void	unlock_forks(t_philo *philo)
// {
// 	pthread_mutex_unlock(philo->fork_1);
// 	pthread_mutex_unlock(philo->fork_2);
// }

// int	start_thinking(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->info->print_mutex);
// 	if (print_action(philo, "is thinking") == 1)
// 	{
// 		pthread_mutex_unlock(&philo->info->print_mutex);
// 		return (1);	
// 	}
// 	pthread_mutex_unlock(&philo->info->print_mutex);
// 	return (0);
// }
