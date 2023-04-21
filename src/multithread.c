/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:01:12 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/21 11:17:32 by vbrouwer         ###   ########.fr       */
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
		if (pthread_create(&philos->info->threads[i], NULL, &routine, (void *)&philos[i])!= 0)
		{
			pthread_mutex_unlock(&philos->info->start_mutex);
			return (EXIT_FAILURE);
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
			// printf("observing %d\n", i);
			if (check_for_eol(&philos[i]) == 1)
			{
				die(&philos[i]);
				return (EXIT_FAILURE);
			}
			i++;
		}
	}
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

// void	*routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *) arg;	
// 	while(1)
// 	{
// 		if (start_eating(philo) == 1)
// 			break ;
// 		start_sleeping(philo);
// 		if (start_thinking(philo) == 1)
// 			break ;
// 		if (philo->meals_done >= philo->info->meals_to_finish && philo->info->meals_to_finish != -1)
// 			break ;
// 	}
// 	return ((void *)philo);
// }
