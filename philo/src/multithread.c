/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:01:12 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/12 09:17:28 by vbrouwer         ###   ########.fr       */
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
	return (SUCCESS);
}

int	observe(t_philo *philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philos->info->philo_count)
		{
			pthread_mutex_lock(&philos->info->check_for_eol_mutex);
			if (check_for_eol(&philos[i]) == 1)
			{
				philos->info->is_dead = true;
				pthread_mutex_unlock(&philos->info->check_for_eol_mutex);
				return (ERROR);
			}
			pthread_mutex_unlock(&philos->info->check_for_eol_mutex);
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
			return (clean_philos(philos, philos->info->philo_count), ERROR);
		i++;
	}
	return (SUCCESS);
}
