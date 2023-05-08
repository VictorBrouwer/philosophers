/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:18:53 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/08 11:22:16 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_philo *philos)
{
	clean_mutexes(philos);
	deallocate_mem(philos);
}

void	clean_mutexes(t_philo *philos)
{
	int	i;

	pthread_mutex_destroy(&philos->info->death_mutex);
	pthread_mutex_destroy(&philos->info->full_philo_mutex);
	pthread_mutex_destroy(&philos->info->start_mutex);
	i = 0;
	while (i < philos->info->philo_count)
	{
		pthread_mutex_destroy(&philos->info->forks[i]);
		pthread_mutex_destroy(&philos[i].print_mutex);
		pthread_mutex_destroy(&philos[i].meals_mutex);
		i++;
	}
}

void	deallocate_mem(t_philo *philos)
{
	free(philos->info->threads);
	free(philos->info->forks);
	free(philos);
}
