/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:01:12 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/25 16:08:05 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	multi_thread(t_philo *philos)
{
	int				i;

	i = 0;
	pthread_mutex_lock(&philos->info->start_mutex);
	while (i < philos->info->philo_count)
	{
		if (pthread_create(&philos->info->threads[i], NULL, &routine, \
		(void *)&philos[i]) != 0)
		{
			pthread_mutex_unlock(&philos->info->start_mutex);
			return (ERROR);
		}
		i++;
	}
	philos->info->start_of_day = get_time_start();
	pthread_mutex_unlock(&philos->info->start_mutex);
	return (EXIT_SUCCESS);
}

int	observe(t_philo *philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philos->info->philo_count)
		{
			if (check_for_eol(&philos[i]) == 1)
				return (die(&philos[i]), ERROR);
			if (philos->info->meals_to_finish != -1)
			{
				pthread_mutex_lock(&philos->info->full_philo_mutex);
				if (philos->info->full_philo_count >= philos->info->philo_count)
				{
					die(&philos[i]);
					pthread_mutex_unlock(&philos->info->full_philo_mutex);
					return (ERROR);
				}
				pthread_mutex_unlock(&philos->info->full_philo_mutex);
			}
			i++;
		}
	}
}

int	join_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->philo_count)
	{
		if (pthread_join(philos->info->threads[i], NULL) != 0)
			exit(ERROR);
		i++;
	}
	return (EXIT_SUCCESS);
}
