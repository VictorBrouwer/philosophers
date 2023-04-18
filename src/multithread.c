/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:01:12 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/18 11:05:58 by vbrouwer         ###   ########.fr       */
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
	while (1)
	{
		if (philos->info->is_dead == 1)
			return (EXIT_FAILURE);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;	
	while(1)
	{
		start_eating(philo);
		start_sleeping(philo);
		start_thinking(philo);
		if (philo->meals_done >= philo->info->meals_to_finish && philo->info->meals_to_finish != -1)
			break ;
	}
	return ((void *)philo);
}
