/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:37:56 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/18 17:37:24 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"philo.h"

unsigned long	get_time_start(void)
{
	struct	timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit(EXIT_FAILURE);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

unsigned long	get_time(t_philo *philo)
{
	// pthread_mutex_lock(&philo->info->time_mutex);
	return ((get_time_start() - philo->info->start_of_day));
	// pthread_mutex_unlock(&philo->info->time_mutex);
}