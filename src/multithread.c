/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:01:12 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/13 13:53:47 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	multi_thread(t_info *info)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * info->philo_count);
	if (!threads)
		return(ft_putstr_fd("malloc error", STDERR_FILENO));
	i = 0;
	while (i < info->philo_count)
	{
		if (pthread_create(&threads[i], NULL, &routine, (void *)&info->philos[i])!= 0)
			exit(EXIT_FAILURE);
		i++;
	}
	i = 0;
	while(i < info->philo_count)
	{
		if (pthread_join(threads[i], (void **) &info->philos[i]) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
	return ;
}

void	*routine(void *philos_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philos_arg;
	while(philo->is_dead == 0)
	{
		start_eating(philo);
		start_sleeping(philo);
		start_thinking(philo);
		if (philo->meals_done >= philo->meals_to_finish && philo->meals_to_finish != -1)
			break ;
	}
	return ((void *)philo);
}

void	start_sleeping(t_philo *philo)
{
	struct timeval tv;

	if (philo->is_dead == 1)
		return ;
	if (gettimeofday(&tv, NULL) == -1)
		exit(EXIT_FAILURE);
	printf("%d %d is sleeping\n", (tv.tv_usec / 1000), philo->id);
	usleep(1000 * philo->time_to_sleep);
}

void	start_thinking(t_philo *philo)
{
	struct timeval tv;

	if (philo->is_dead == 1)
		return ;
	if (gettimeofday(&tv, NULL) == -1)
		exit(EXIT_FAILURE);
	printf("%d %d is thinking\n", (tv.tv_usec / 1000), philo->id);
}
