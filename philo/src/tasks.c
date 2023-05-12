/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:14:53 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/11 17:14:30 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->info->start_mutex);
	pthread_mutex_unlock(&philo->info->start_mutex);
	if ((philo->id % 2) == 1)
		uneven_group(philo);
	else
		even_group(philo);
	return (NULL);
}

void	uneven_group(t_philo *philo)
{
	while (1)
	{
		if (print_action(philo, "is sleeping") == 1)
			break ;
		start_sleeping(philo, philo->info->time_to_sleep);
		if (print_action(philo, "is thinking") == 1)
			break ;
		if (start_eating(philo) == 1)
			break ;
	}
}

void	even_group(t_philo *philo)
{
	while (1)
	{
		if (print_action(philo, "is thinking") == 1)
			break ;
		if (start_eating(philo) == 1)
			break ;
		if (print_action(philo, "is sleeping") == 1)
			break ;
		start_sleeping(philo, philo->info->time_to_sleep);
	}
}

int	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->info->check_for_eol_mutex);
	if (check_for_eol(philo) == 1)
	{
		pthread_mutex_unlock(&philo->info->check_for_eol_mutex);
		return (ERROR);
	}
	printf("%lu %d %s\n", get_time(philo), philo->id, action);
	pthread_mutex_unlock(&philo->info->check_for_eol_mutex);
	return (0);
}
