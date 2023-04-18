/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:01:12 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/18 16:56:48 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	multi_thread(t_philo *philos)
{
	int				i;

	i = 0;
	while (i < philos->info->philo_count)
	{
		if (pthread_create(&philos->info->threads[i], NULL, &routine, (void *)&philos[i])!= 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	join_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while(i < philos->info->philo_count)
	{
		if (pthread_join(philos->info->threads[i], NULL) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	observe(t_philo *philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i <= philos->info->philo_count)
		{
			printf("observing %d\n", i);
			if (check_for_death(&philos[i]) == 1)
				return (EXIT_FAILURE);
			// pthread_mutex_lock(&philos->info->start_mutex);
			// pthread_mutex_unlock(&philos->info->start_mutex);
			i++;
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;	
	while(1)
	{
		// pthread_mutex_lock(&philo->info->start_mutex);
		start_eating(philo);
		start_sleeping(philo);
		start_thinking(philo);
		if (philo->meals_done >= philo->info->meals_to_finish && philo->info->meals_to_finish != -1)
			break ;
		// pthread_mutex_unlock(&philo->info->start_mutex);
	}
	return ((void *)philo);
}
